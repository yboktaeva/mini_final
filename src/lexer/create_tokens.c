/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 10:59:20 by yuboktae          #+#    #+#             */
/*   Updated: 2023/10/04 20:14:17 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"
#include "utils.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "../libft/libft.h"

t_token	*tokenize_input(t_env *env, char *line)
{
	t_token	*tokens;
	int		is_correct;

	is_correct = 0;
	tokens = malloc(sizeof(t_token));
	if (!tokens)
		return (NULL);
	init_token_list(tokens);
	if (check_quotes(line))
	{
		free_token(tokens);
		quote_error();
		return (NULL);
	}
	is_correct = split_tokens(env, line, &tokens);
	if (is_correct != 1)
	{
		free_token(tokens);
		return (NULL);
	}
	remove_quote(tokens);
	return (tokens);
}

void	init_token_list(t_token *new)
{
	new->type = 0;
	new->value = NULL;
	new->next = NULL;
}

int	split_tokens(t_env *env, char *line, t_token **tokens)
{
	int				start;
	int				end;
	t_type			type;

	type = 0;
	end = 0;
	while (line[end] != '\0')
	{
		end = pass_white_space(line, end);
		if (line[end] == '\0')
			break ;
		start = end;
		if (is_operator(line[end]))
			end = get_operator_index(line, end, &type);
		else
			end = get_token_index(line, end, WORD, &type);
		if (type == WORD)
			word_token_add(tokens, type, if_dollar(env,
					ft_substr(line, start, end - start + 1)));
		else
			token_add(tokens, type, ft_substr(line, start, end - start + 1));
		end++;
	}
	return (1);
}

t_token	*new_token_node(t_type type, char *value)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	init_token_list(new);
	new->type = type;
	new->value = value;
	return (new);
}

void	token_add(t_token **head, t_type type, char *value)
{
	t_token	*curr;

	if (*head == NULL)
	{
		free(*head);
		*head = new_token_node(type, value);
	}
	else
	{
		curr = *head;
		while (curr->next)
			curr = curr->next;
		curr->next = new_token_node(type, value);
		if (curr->next == NULL)
			return ;
	}
}
