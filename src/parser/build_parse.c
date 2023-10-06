/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 15:10:29 by yuboktae          #+#    #+#             */
/*   Updated: 2023/10/05 09:50:03 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "utils.h"
#include "minishell.h"
#include <stdio.h>

static int	fill_parse_list(t_parse_list *parse_list, t_token *tokens);
static int	handle_pipe_token(t_token **curr, t_parse_list **parse_list);

t_parse_list	*parsing_tokens(t_token *tokens)
{
	int				is_correct;
	t_parse_list	*parse_list;

	is_correct = 0;
	parse_list = NULL;
	if (!tokens)
		return (NULL);
	parse_list = init_parse_list();
	is_correct = fill_parse_list(parse_list, tokens);
	{
		if (is_correct == -1)
		{
			free_parse_list(parse_list);
			return (NULL);
		}
	}
	return (parse_list);
}

static int	fill_parse_list(t_parse_list *parse_list, t_token *tokens)
{
	int		i;
	t_token	*curr;

	i = 0;
	curr = tokens->next;
	while (curr)
	{
		if (!invalid_operator(curr))
			return (-1);
		if (is_word(curr->type))
			if_word_token(curr, parse_list);
		else if (is_redir(curr->type))
		{
			if (if_redir_token(curr, parse_list) == NULL)
				return (-1);
			curr = curr->next;
		}
		else
		{
			if (handle_pipe_token(&curr, &parse_list) == -1)
				return (-1);
		}
		curr = curr->next;
	}
	return (1);
}

static int	handle_pipe_token(t_token **curr, t_parse_list **parse_list)
{
	if (if_pipe_token(*curr, *parse_list) == NULL)
		return (-1);
	*parse_list = (*parse_list)->next;
	return (1);
}

// static int	fill_parse_list(t_parse_list *parse_list, t_token *tokens)
// {
// 	int		i;
// 	t_token *curr;

// 	i = 0;
// 	curr = tokens->next;
// 	while (curr)
// 	{
// 		if (!invalid_operator(curr))
// 			return (-1);
// 		if (is_word(curr->type))
// 			if_word_token(curr, parse_list);
// 		else if (is_redir(curr->type))
// 		{
// 			if (if_redir_token(curr, parse_list) == NULL)
// 				return (-1);
// 			curr = curr->next;
// 		}
// 		else
// 		{
// 			if (if_pipe_token(curr, parse_list) == NULL)
// 				return (-1);
// 			parse_list = parse_list->next;
// 		}
// 		curr = curr->next;
// 	}
// 	return (1);
// }
