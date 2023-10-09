/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 12:30:10 by yuboktae          #+#    #+#             */
/*   Updated: 2023/10/09 19:04:31 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "exec.h"
#include "minishell.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>

static t_here_doc	*run_heredoc(t_table *main, t_redir *input,
					t_cmd_info *cmd_info);
static int			write_heredoc(t_table *main, int *tmp_fd, char *sep);


static int	get_exit_status(int status)
{
	int	return_code;
	int	signal;

	return_code = 0;
	signal = 0;
	if (WIFEXITED(status))
		return_code = WEXITSTATUS(status);
	else
	{
		return_code = 128;
		if (WIFSIGNALED(status))
			signal = WTERMSIG(status);
		else
		{
			if (WIFSTOPPED(status))
				signal = SIGSTOP;
			if (WIFCONTINUED(status))
				signal = SIGCONT;
		}			
	}
	return (g_status = return_code + signal);
}


void	open_heredoc(t_table *main, t_parse_list *parse_list,
		t_cmd_info *cmd_info)
{
	t_redir	*curr;

	main->here_doc = malloc(sizeof(t_here_doc));
	if (!main->here_doc)
	{
		perror("Malloc failure in open heredoc");
		return ;
	}
	main->here_doc->read_fd = 0;
	main->here_doc->next = NULL;
	while (parse_list)
	{
		curr = parse_list->input;
		if (curr != NULL)
		{
			if (!run_heredoc(main, curr, cmd_info))
			{
				return ;
			}
		}
		parse_list = parse_list->next;
	}
}

static t_here_doc	*run_heredoc(t_table *main, t_redir *input,
			t_cmd_info *cmd_info)
{
	int		fd[2];
	pid_t	pid_heredoc;
	int		status;

	(void)cmd_info;
	while (input != NULL)
	{
		if (input->type == HEREDOC)
		{
			if (pipe(fd) == -1)
				free_n_close_heredoc(&main->here_doc, fd[0]);
			pid_heredoc = fork();
			if (pid_heredoc == 0)
			{
				ft_close(fd[0]);
				write_heredoc(main, fd, input->file_name);
				ft_close(fd[1]);
			}
			else
			{
				ft_close(fd[1]);
				wait(&status);
				if (get_exit_status(status) == 1)
					return (free_n_close_heredoc(&main->here_doc, fd[0]));
				else
					add_back_heredoc(main->here_doc, fd[0]);
				// cmd_info->in = dup(fd[0]);
				// ft_close(main->cmd_info->in);
				// handle_sig(SIG_DEFAULT);
			}
		}
		input = input->next;
	}
	return (main->here_doc);
}

static int	write_heredoc(t_table *main, int *tmp_fd, char *sep)
{
	char	*input;
	(void)main;
	handle_sig(SIG_HEREDOC);
	while (1)
	{
		input = readline(">");
		if (input)
		{
			if (ft_strncmp(sep, input, ft_strlen(sep)))
			{
				write(tmp_fd[1], input, ft_strlen(input));
				write(tmp_fd[1], "\n", 1);
				free(input);
			}
			else
			{
				break ;
			}
		}
	}
	free(input);
	ft_close(tmp_fd[0]);
	ft_close(tmp_fd[1]);
	exit (0);
}