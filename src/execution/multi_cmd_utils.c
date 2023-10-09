/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_cmd_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 14:54:25 by asekmani          #+#    #+#             */
/*   Updated: 2023/10/09 17:44:58 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "builtin.h"
#include "exec.h"
#include "parser.h"
#include "utils.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void	ft_close(int fd)
{
	if (fd > 0)
		close(fd);
}

void	close_fd_cmd(t_cmd_info *cmd_info)
{
	ft_close(cmd_info->fd[1]);
	ft_close(cmd_info->fd[0]);
	if (cmd_info->in != STDIN_FILENO)
		ft_close(cmd_info->in);
	if (cmd_info->out != STDOUT_FILENO)
		ft_close(cmd_info->out);
}

int	wait_all_pid(t_cmd_info *cmd_info, pid_t pid)
{
	int	save_status;
	int	status;

	(void)cmd_info;
	save_status = 0;
	pid = waitpid(-1, &status, 0);
	while (pid > 0)
	{
		pid = waitpid(-1, &status, 0);
		status = save_status;
	}
	if (WIFEXITED(save_status))
		status = WEXITSTATUS(save_status);
	else if (WIFSIGNALED(status))
		status = 128 + WTERMSIG(save_status);
	else
		status = save_status;
	return (status);
}

void	reset_cmd_info(t_cmd_info *cmd_info)
{
	cmd_info->out = STDOUT_FILENO;
	cmd_info->in = STDIN_FILENO;
}
