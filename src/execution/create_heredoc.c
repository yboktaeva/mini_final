/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 12:30:10 by yuboktae          #+#    #+#             */
/*   Updated: 2023/10/10 15:21:06 by yuboktae         ###   ########.fr       */
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

static t_here_doc	*run_heredoc(t_table *main, t_redir *input);
static void			parent_heredoc(t_here_doc *here_doc, int *status, int *fd);
static int			write_heredoc(t_table *main, int *tmp_fd, char *sep);
static void			free_and_close(t_table *main, int *tmp_fd);

void	open_heredoc(t_table *main, t_parse_list *parse_list)
{
	t_redir	*curr;

	main->here_doc = malloc(sizeof(t_here_doc));
	if (!main->here_doc)
	{
		perror("Malloc failure in open heredoc");
		return ;
	}
	main->here_doc->read_fd = STDIN_FILENO;
	main->here_doc->next = NULL;
	handle_sig(SIG_DEFAULT);
	while (parse_list)
	{
		curr = parse_list->input;
		if (curr != NULL)
		{
			if (!run_heredoc(main, curr))
			{
				free_n_close_heredoc(&main->here_doc, main->here_doc->read_fd);
				return (free(main->here_doc));
			}
		}
		parse_list = parse_list->next;
	}
	handle_sig(SIG_DEFAULT);
}

static t_here_doc	*run_heredoc(t_table *main, t_redir *input)
{
	pid_t	pid_heredoc;
	int		status;
	int		fd[2];

	while (input != NULL)
	{
		if (input->type == HEREDOC)
		{
			if (pipe(fd) == -1)
				free_and_close(main, fd);
			pid_heredoc = fork();
			if (pid_heredoc == 0)
			{
				ft_close(fd[0]);
				write_heredoc(main, fd, input->file_name);
				ft_close(fd[1]);
			}
			else
				parent_heredoc(main->here_doc, &status, fd);
		}
		input = input->next;
	}
	return (main->here_doc);
}

static void	parent_heredoc(t_here_doc *here_doc, int *status, int *fd)
{
	wait(status);
	ft_close(fd[1]);
	add_back_heredoc(here_doc, here_doc->read_fd);
	here_doc->read_fd = dup(fd[0]);
	ft_close(fd[0]);
	handle_sig(SIG_DEFAULT);
}

static int	write_heredoc(t_table *main, int *tmp_fd, char *sep)
{
	char	*input;

	handle_sig(SIG_HEREDOC);
	while (1)
	{
		g_status = 0;
		input = readline(">");
		if (!input)
			break ;
		else
		{
			if (ft_strncmp(sep, input, ft_strlen(sep)))
			{
				write(tmp_fd[1], input, ft_strlen(input));
				write(tmp_fd[1], "\n", 1);
			}
			else
			{
				free(input);
				break ;
			}
		}
	}
	free_and_close(main, tmp_fd);
	exit(0);
}

static void	free_and_close(t_table *main, int *tmp_fd)
{
	ft_close(tmp_fd[0]);
	ft_close(tmp_fd[1]);
	free_env(&main->env);
	free_execution(main);
	free_n_close_heredoc(&main->here_doc, main->here_doc->read_fd);
}
