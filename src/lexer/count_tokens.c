/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 15:32:08 by yuboktae          #+#    #+#             */
/*   Updated: 2023/10/04 20:15:40 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "utils.h"
#include <stddef.h>

int	is_operator(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (1);
	return (0);
}

int	get_quote_index(char *line, int i, t_type type)
{
	if (type == S_QUOT)
	{
		while (line[i] != '\'' && line[i + 1] != '\0')
			++i;
	}
	else if (type == D_QUOT && line[i + 1] != '\0')
	{
		while (line[i] != '\"' && line[i + 1] != '\0')
			++i;
	}
	return (i);
}

int	get_token_index(char *line, int i, t_type curr_type, t_type *type)
{
	*type = curr_type;
	if (curr_type == WORD)
	{
		while (line[i + 1] != '\0')
		{
			if (line[i] == '\'')
				i = get_quote_index(line, i + 1, S_QUOT);
			else if (line[i] == '\"')
				i = get_quote_index(line, i + 1, D_QUOT);
			if (ft_isspace(line[i + 1]) || is_operator(line[i + 1])
				|| line[i + 1] == '\0')
				return (i);
			++i;
		}
	}
	else if (curr_type == REDIR_IN || curr_type == REDIR_OUT
		|| curr_type == PIPE)
		i = i + 0;
	else if (curr_type == HEREDOC || curr_type == APPEND)
		i = i + 1;
	return (i);
}

int	get_operator_index(char *line, int i, t_type *type)
{
	if (line[i] == '<')
	{
		if (line[i + 1] == '<')
			return (get_token_index(line, i, HEREDOC, type));
		else
			return (get_token_index(line, i, REDIR_IN, type));
	}
	else if (line[i] == '>')
	{
		if (line[i + 1] == '>')
			return (get_token_index(line, i, APPEND, type));
		else
			return (get_token_index(line, i, REDIR_OUT, type));
	}
	else if (line[i] == '|')
		return (get_token_index(line, i, PIPE, type));
	return (i);
}
