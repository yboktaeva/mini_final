/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 16:18:03 by yuboktae          #+#    #+#             */
/*   Updated: 2023/10/04 17:24:36 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	check_quotes(char *s)
{
	int	i;
	int	quote_flag;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\'' || s[i] == '\"')
		{
			quote_flag = s[i];
			i++;
			while (s[i] != '\0' && s[i] != quote_flag)
				i++;
			if (s[i] == '\0')
				return (1);
		}
		++i;
	}
	return (0);
}

void	remove_quote(t_token *tokens)
{
	t_token	*curr;

	curr = tokens->next;
	while (curr)
	{
		if (curr->type == WORD)
			get_rid_quotes(curr->value);
		curr = curr->next;
	}
}

void	get_rid_quotes(char *value)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (value[i] != '\0')
	{
		if (value[i] == '\'')
			if_quotes_in_quotes(value, '\'', &i, &j);
		else if (value[i] == '\"')
			if_quotes_in_quotes(value, '\"', &i, &j);
		else
		{
			value[j] = value[i];
			++j;
			++i;
		}
	}
	value[j] = '\0';
}

void	if_quotes_in_quotes(char *str, char quote_flag, int *i, int *j)
{
	if (check_quotes(str + *i))
	{
		while (str[*i])
		{
			str[*j] = str[*i];
			(*j)++;
			(*i)++;
		}
	}
	else
	{
		(*i)++;
		while (str[*i] != quote_flag)
		{
			str[*j] = str[*i];
			(*j)++;
			(*i)++;
		}
		(*i)++;
	}
}
