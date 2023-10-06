/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 15:47:52 by yuboktae          #+#    #+#             */
/*   Updated: 2023/10/04 13:19:05 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "lexer.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

int	word_token_index(char *line, int i)
{
	while (line[i + 1] != '\0')
	{
		if (line[i] == '\'')
			i = get_quote_index(line, i + 1, S_QUOT);
		else if (line[i] == '\"')
			i = get_quote_index(line, i + 1, D_QUOT);
		if (ft_isspace(line[i + 1]) || line[i + 1] == '\0')
			return (i);
		++i;
	}
	return (i);
}

void	word_token_add(t_token **tokens, t_type type, char *expand_str)
{
	int				start;
	int				end;

	start = 0;
	end = 0;
	while (expand_str[end] != '\0')
	{
		end = pass_white_space(expand_str, end);
		if (expand_str[end] == '\0')
			break ;
		start = end;
		end = word_token_index(expand_str, end);
		token_add(tokens, type, ft_substr(expand_str, start, end - start + 1));
		end++;
	}
	free(expand_str);
}

char	*if_dollar(t_env *env, char *expand_str)
{
	int	i;
	int	double_quote;

	i = 0;
	double_quote = 0;
	while (expand_str[i])
	{
		if (expand_str[i] == '\"')
			double_quote = !double_quote;
		if (expand_str[i] == '\'' && double_quote == 0)
			skip_single_quote(expand_str, &i);
		else
			if (expand_str[i] == '$')
				join_before_and_after(env, &expand_str, &i);
		i++;
	}
	return (expand_str);
}
