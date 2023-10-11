/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 11:16:59 by yuboktae          #+#    #+#             */
/*   Updated: 2023/10/10 12:43:37 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	is_redir(t_type type)
{
	if (type == REDIR_IN || type == HEREDOC
		|| type == REDIR_OUT || type == APPEND)
		return (1);
	return (0);
}

t_type	type_of_redir(t_type type)
{
	if (type == REDIR_IN || type == HEREDOC
		|| type == REDIR_OUT || type == APPEND)
		return (type);
	return (0);
}

int	is_word(t_type type)
{
	if (type == WORD)
		return (1);
	return (0);
}

int	is_pipe(t_type type)
{
	if (type == PIPE)
		return (1);
	return (0);
}
