/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 00:06:08 by yuliaboktae       #+#    #+#             */
/*   Updated: 2023/10/06 17:20:27 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "builtin.h"
#include "exec.h"
#include "minishell.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void	init_cmd_info(t_cmd_info *cmd_info, t_parse_list *s);
static void	execute_command(t_parse_list *s, t_table *main, int flag_redir,
				int *tmp_fd);

void	cmd_execution(t_parse_list *parse_list, t_table *main)
{
	t_cmd_info	cmd_info;
	int			tmp_fd[2];

	init_cmd_info(&cmd_info, parse_list);
	main->cmd_info = &cmd_info;
	open_heredoc(main, parse_list, &cmd_info);
	if (!parse_list->one_cmd && (parse_list->input || parse_list->output))
		if_only_redir(parse_list, main, tmp_fd);
	if (cmd_info.nb_cmds == 1) //
	{
		if (is_builtin(parse_list->one_cmd))
			one_builtin(parse_list, main, &cmd_info);
		else
			one_cmd_exec(parse_list, main, &cmd_info);
	}
	else //
		multi_cmds_exec(parse_list, main, &cmd_info);
	free_n_close_heredoc(&main->here_doc, 0);
	free(main->here_doc);
	main->here_doc = NULL;
	return ;
}

static void	init_cmd_info(t_cmd_info *cmd_info, t_parse_list *s)
{
	cmd_info->fd[0] = -1;
	cmd_info->fd[1] = -1;
	cmd_info->nb_cmds = cmd_size(s);
	cmd_info->in = 0;
	cmd_info->out = 1;
}

void	one_builtin(t_parse_list *parse_list, t_table *main,
		t_cmd_info *cmd_info)
{
	int	flag_redir;
	int	tmp_fd[2];

	if (ft_strcmp(parse_list->one_cmd->str, "exit") == 0)
		builtin_exec(parse_list->one_cmd, main->env, ONE_CMD, main);
	else
	{
		tmp_fd[0] = dup(STDIN_FILENO);
		tmp_fd[1] = dup(STDOUT_FILENO);
		flag_redir = handle_io_redir(parse_list, main, cmd_info);
		execute_command(parse_list, main, flag_redir, tmp_fd);
	}
}

static void	execute_command(t_parse_list *s, t_table *main, int flag_redir,
		int *tmp_fd)
{
	builtin_exec(s->one_cmd, main->env, ONE_CMD, main);
	if (flag_redir)
	{
		dup2(tmp_fd[0], STDIN_FILENO);
		dup2(tmp_fd[1], STDOUT_FILENO);
	}
	close(tmp_fd[0]);
	close(tmp_fd[1]);
}
