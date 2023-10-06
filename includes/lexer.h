/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 17:55:34 by yuboktae          #+#    #+#             */
/*   Updated: 2023/10/04 20:41:43 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "struct.h"
/*ENV*/
t_env	*init_env_list(char **envp);
void	get_env(t_env *head, char *str);
/*LEXER*/
int		split_tokens(t_env *env, char *line, t_token **tokens);
t_token	*tokenize_input(t_env *env, char *line);
char	*if_dollar(t_env *env, char *expand_str);
int		dollar_sign(char *str);
void	join_before_and_after(t_env *env, char **str, int *i);
char	*find_var_value(t_env *env, char *str, int *i);
void	if_quotes_in_quotes(char *str, char quote_flag, int *i, int *j);
void	init_token_list(t_token *new);
t_token	*new_token_node(t_type type, char *value);
void	token_add(t_token **head, t_type type, char *value);
void	word_token_add(t_token **tokens, t_type type, char *expand_str);
int		word_token_index(char *line, int i);
void	remove_quote(t_token *tokens);
int		is_operator(char c);
int		get_quote_index(char *line, int i, t_type type);
int		get_token_index(char *line, int i, t_type curr_type, t_type *type);
int		get_operator_index(char *line, int i, t_type *type);
void	get_rid_quotes(char *value);

#endif
