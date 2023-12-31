/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 16:01:44 by yuboktae          #+#    #+#             */
/*   Updated: 2023/09/30 18:13:53 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "exec.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

static char	**convert_parse_list(t_one_cmd *head);

void	create_args(t_parse_list *parse_list, t_arg *arg)
{
	t_parse_list	*head;

	head = parse_list;
	arg->argv = convert_parse_list(head->one_cmd);
	arg->n_args = num_args(head->one_cmd);
}

static char	**convert_parse_list(t_one_cmd *head)
{
	int			i;
	int			size;
	char		**arr;
	t_one_cmd	*curr_cmd;

	size = num_args(head);
	curr_cmd = head;
	arr = (char **)malloc(sizeof(char *) * (size + 2));
	if (!arr)
	{
		perror("Malloc failure in create_args");
		return (NULL);
	}
	i = 0;
	while (i < size)
	{
		arr[i] = ft_strdup(curr_cmd->str);
		i++;
		curr_cmd = curr_cmd->next;
	}
	arr[size] = NULL;
	return (arr);
}

void	check_free(int *fd)
{
	if (fd != NULL)
	{
		free(fd);
		fd = NULL;
	}
}
