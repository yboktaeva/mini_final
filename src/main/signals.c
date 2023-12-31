/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 17:07:01 by asekmani          #+#    #+#             */
/*   Updated: 2023/10/10 13:11:57 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"
#include "../libft/libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

void	default_sigint(int sig)
{
	(void)sig;
	g_status = 130;
	ft_putstr_fd("\n", STDERR_FILENO);
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
}

void	sig_here_doc(int sig)
{
	if (sig == SIGINT)
	{
		g_status = 130;
		ft_putstr_fd("\n", STDERR_FILENO);
		close(0);
		close(1);
	}
}

void	sig_parent(int sig)
{
	if (sig == SIGINT)
		ft_putstr_fd("\n", STDERR_FILENO);
	else if (sig == SIGQUIT)
		ft_putstr_fd("Quit: Core dumped\n", STDERR_FILENO);
}

void	handle_sig(int state)
{
	if (state == SIG_DEFAULT)
	{
		signal(SIGINT, default_sigint);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (state == SIG_HEREDOC)
	{
		signal(SIGINT, &sig_here_doc);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (state == SIG_CHILD)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
	}
	else if (state == SIG_PARENT)
	{
		signal(SIGINT, &sig_parent);
		signal(SIGQUIT, &sig_parent);
	}
}
