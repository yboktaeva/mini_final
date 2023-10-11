/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_cmds_exec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 15:08:13 by yuboktae          #+#    #+#             */
/*   Updated: 2023/10/10 15:34:38 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "builtin.h"
#include "exec.h"
#include "minishell.h"
#include "parser.h"
#include "utils.h"
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

static int	execute_parent(t_cmd_info *cmd_info, pid_t pid, int *fdc);
static int	execute_command(t_parse_list *parse_list, const char *path,
				t_table *main);

int	multi_cmds_exec(t_parse_list *s, t_table *main, t_cmd_info *cmd_info)
{
	cmd_info->path = get_path_from_envp(main->env);
	cmd_info->index_cmd = 1;
	while (s)
	{
		if (s->one_cmd)
			if_exec_path(s, main, cmd_info);
		s = s->next;
		cmd_info->index_cmd++;
	}
	return (g_status);
}

int	exec_cmd(t_parse_list *parse_list, t_cmd_info *cmd_info, t_table *main)
{
	int	status;

	status = 0;
	reset_cmd_info(cmd_info);
	status = handle_redirections(parse_list, main->here_doc,
			&(main->cmd_info)->in, &(main->cmd_info)->out);
	if (status)
	{
		status = execute_command(parse_list, main->cmd_info->executable_path,
				main);
	}
	reset_cmd_info(main->cmd_info);
	free(cmd_info->executable_path);
	cmd_info->executable_path = NULL;
	return (status);
}

static int	execute_command(t_parse_list *parse_list, const char *path,
		t_table *main)
{
	pid_t	pid;
	int		fdc[2];
	int		status;
	int		res;

	res = -1;
	res = pipe(fdc);
	if (res == -1)
	{
		safe_exit(main);
		return (EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
	{
		safe_exit(main);
		return (EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		handle_sig(SIG_CHILD);
		ft_child(parse_list, path, main, fdc);
	}
	status = execute_parent(main->cmd_info, pid, fdc);
	return (status);
}

static int	execute_parent(t_cmd_info *cmd_info, pid_t pid, int *fdc)
{
	int	status;

	status = 0;
	handle_sig(SIG_PARENT);
	close_fd_cmd(cmd_info);
	if (cmd_info->index_cmd == cmd_info->nb_cmds)
	{
		status = wait_all_pid(cmd_info, pid);
		ft_close(fdc[0]);
		ft_close(fdc[1]);
	}
	else
	{
		cmd_info->fd[0] = dup(fdc[0]);
		cmd_info->fd[1] = dup(fdc[1]);
		ft_close(fdc[0]);
		ft_close(fdc[1]);
	}
	return (status);
}

void	execute_child(t_table *main, t_cmd_info *cmd_info, int *fdc,
		const char *path)
{
	dup_and_close(main->parse_list, cmd_info, fdc);
	free_fake_envp(main);
	main->arg->envp = duplicate_envp(main->env);
	execve(path, main->arg->argv, main->arg->envp);
	if (errno == EACCES)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(main->arg->argv[0]);
		free_execution(main);
		free_env(&main->env);
		free(main->cmd_info->executable_path);
		free_n_close_heredoc(&main->here_doc, 0);
		ft_close(main->cmd_info->fd[0]);
		ft_close(main->cmd_info->fd[1]);
		exit(126);
	}
	ft_close(fdc[1]);
	ft_close(fdc[0]);
	exec_fail(main, *main->arg->argv);
}
