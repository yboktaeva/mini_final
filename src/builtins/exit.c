/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 18:07:41 by yuboktae          #+#    #+#             */
/*   Updated: 2023/10/10 11:25:25 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "exec.h"
#include "utils.h"
#include "minishell.h"
#include "../libft/libft.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void	single_exit(t_table *main);
static int	is_all_digit(char *str);
static void	exit_digit(t_one_cmd *one_cmd, t_table *main);

int	cmd_exit(t_one_cmd *one_cmd, t_table *main)
{
	if (one_cmd->next == NULL)
		single_exit(main);
	else if (one_cmd->next->next != NULL)
	{
		if (!is_all_digit(one_cmd->next->str))
		{
			ft_putendl_fd("exit: numeric argument required", STDERR_FILENO);
			single_exit(main);
		}
		else
			ft_putendl_fd("exit: too many arguments", STDERR_FILENO);
		return (g_status = 1);
	}
	else
	{
		if (is_all_digit(one_cmd->next->str))
			exit_digit(one_cmd, main);
		else
		{
			ft_putendl_fd("exit: numeric argument required", STDERR_FILENO);
			safe_exit(main);
			exit(255);
		}
	}
	return (g_status = 0);
}

static void	single_exit(t_table *main)
{
	ft_putendl_fd("exit", STDOUT_FILENO);
	safe_exit(main);
	exit(g_status);
}

static void	exit_digit(t_one_cmd *one_cmd, t_table *main)
{
	ft_putendl_fd("exit", STDOUT_FILENO);
	g_status = ft_atoi(one_cmd->next->str);
	safe_exit(main);
	exit(g_status);
}

static int	is_all_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]))
			return (0);
		++i;
	}
	return (1);
}
