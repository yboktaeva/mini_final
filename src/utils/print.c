/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 17:41:43 by yuboktae          #+#    #+#             */
/*   Updated: 2023/10/05 09:45:18 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

void	print_env_list(t_env *env)
{
	t_env	*head;

	if (!env)
		exit (1);
	head = env->next;
	while (head != NULL)
	{
		if (head->var_value != NULL)
			printf("%s=%s\n", head->var_name, head->var_value);
		head = head->next;
	}
	return ;
}

void	print_tokens(t_token *tokens)
{
	t_token	*curr;

	curr = tokens->next;
	while (curr)
	{
		printf("%s   token_type: %d\n", curr->value, curr->type);
		curr = curr->next;
	}
}

void	print_parse_list(t_parse_list *parse_list)
{
	t_one_cmd	*cur_cmd;
	t_redir		*cur_redir;

	while (parse_list != NULL)
	{
		cur_cmd = parse_list->one_cmd;
		while (cur_cmd != NULL)
		{
			printf("CMD %s\n", cur_cmd->str);
			cur_cmd = cur_cmd->next;
		}
		cur_redir = parse_list->input;
		while (cur_redir != NULL)
		{
			printf("T: %d, F: %s\n", cur_redir->type, cur_redir->file_name);
			cur_redir = cur_redir->next;
		}
		cur_redir = parse_list->output;
		while (cur_redir != NULL)
		{
			printf("T: %d, F: %s\n", cur_redir->type, cur_redir->file_name);
			cur_redir = cur_redir->next;
		}
		parse_list = parse_list->next;
	}
}
