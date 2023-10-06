/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_analyse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 16:52:40 by yuboktae          #+#    #+#             */
/*   Updated: 2023/10/04 21:13:36 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"
#include "../libft/libft.h"
#include "utils.h"
#include <stdlib.h>

void	if_word_token(t_token *tokens, t_parse_list *parse_list)
{
	t_one_cmd	*one_cmd;

	one_cmd = init_one_cmd(tokens->value);
	one_cmd_node(&parse_list->one_cmd, one_cmd);
}

void	*if_pipe_token(t_token *tokens, t_parse_list *parse_list)
{
	t_parse_list	*node;

	if (!tokens->next && is_pipe(tokens->type))
		return (syntax_error(tokens->value));
	else if (is_pipe(tokens->type) && is_pipe(tokens->next->type)
		&& tokens->next->next == NULL)
		return (syntax_error("||"));
	else
	{
		node = init_parse_list();
		add_node(parse_list, node);
	}
	return (node);
}

void	*if_redir_token(t_token *tokens, t_parse_list *parse_list)
{
	t_redir	*node;

	if (!tokens->next || tokens->next->type != WORD)
		return (syntax_error("newline"));
	node = init_redir_list(tokens->type, tokens->next->value);
	if (tokens->type == REDIR_IN || tokens->type == HEREDOC)
		redir_node(&parse_list->input, node);
	else
		redir_node(&parse_list->output, node);
	return (node);
}

void	*invalid_operator(t_token *tokens)
{
	if (ft_strcmp(tokens->value, "&") == 0
		|| ft_strcmp(tokens->value, "&&") == 0
		|| ft_strcmp(tokens->value, ";") == 0)
		syntax_error(tokens->value);
	return (SUCCES);
}
