/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 18:59:21 by yuboktae          #+#    #+#             */
/*   Updated: 2023/10/10 15:52:10 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "exec.h"
#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>

int	exec_fail(t_table *main, char *str)
{
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putendl_fd(" : command not found", STDERR_FILENO);
	free_execution(main);
	free_env(&main->env);
	free(main->cmd_info->executable_path);
	free_n_close_heredoc(&main->here_doc, main->here_doc->read_fd);
	ft_close(main->cmd_info->fd[0]);
	ft_close(main->cmd_info->fd[1]);
	g_status = 127;
	exit(g_status);
}
