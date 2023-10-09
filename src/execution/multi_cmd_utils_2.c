/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_cmd_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 20:59:30 by asekmani          #+#    #+#             */
/*   Updated: 2023/10/09 17:59:05 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "exec.h"
#include "minishell.h"
#include "parser.h"
#include "utils.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void	close_cmd_fd(t_cmd_info *cmd_info, int *fdc)
{
	ft_close(fdc[0]);
	ft_close(fdc[1]);
	ft_close(cmd_info->fd[0]);
	ft_close(cmd_info->fd[1]);
}

void	dup_and_close(t_parse_list *s, t_cmd_info *cmd_info, int *fdc)
{
	(void)s;
	if (cmd_info->in != STDIN_FILENO)
	{
		dup2(cmd_info->in, STDIN_FILENO);
		ft_close(cmd_info->in);
	}
	else if (cmd_info->index_cmd > 1 && cmd_info->fd[0] != -1)
	{
		dup2(cmd_info->fd[0], STDIN_FILENO);
		if (!is_builtin(s->one_cmd) && !cmd_info->out && !cmd_info->in)
			ft_close(cmd_info->fd[0]);
		ft_close(cmd_info->fd[1]);
	}
	if (cmd_info->out != STDOUT_FILENO)
	{
		dup2(cmd_info->out, STDOUT_FILENO);
		ft_close(cmd_info->out);
	}
	else if (cmd_info->index_cmd != cmd_info->nb_cmds)
	{
		ft_close(fdc[0]);
		dup2(fdc[1], STDOUT_FILENO);
		ft_close(fdc[1]);
	}
	if (cmd_info->index_cmd == cmd_info->nb_cmds)
		close_cmd_fd(cmd_info, fdc);
}

void	ft_child(t_parse_list *parse_list, const char *path, t_table *main,
		int *fdc)
{
	if (is_builtin(parse_list->one_cmd))
	{
		dup_and_close(parse_list, main->cmd_info, fdc);
		free(main->cmd_info->executable_path);
		free_token(main->tokens);
		free_fake_envp(main);
		free_n_close_heredoc(&main->here_doc, 0);
		builtin_exec(parse_list->one_cmd, main->env, MULTI_CMD, main);
	}
	else
	{
		create_args(parse_list, main->arg);
		execute_child(main, main->cmd_info, fdc, path);
	}
}
