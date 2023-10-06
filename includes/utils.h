/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 18:24:21 by yuboktae          #+#    #+#             */
/*   Updated: 2023/10/05 10:55:39 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "struct.h"

char	**duplicate_envp(t_env *env);
int		ft_isspace(char c);
void	skip_single_quote(char *str, int *i);
int		pass_white_space(char *s, int i);
int		check_quotes(char *s);
t_type	type_of_redir(t_type type);
int		is_redir(t_type type);
int		is_word(t_type type);
int		is_pipe(t_type type);
void	print_tokens(t_token *tokens);
void	print_env_list(t_env *env);
void	print_parse_list(t_parse_list *parse_list);
int		cmd_size(t_parse_list *parse_list);
int		num_args(t_one_cmd *one_cmd);
int		env_size(t_env *env);
char	*env_var_name(char *str);
int		env_var_name_len(char *var_name);
char	*env_var_value(t_env *env, char *key);
t_env	*get_last(t_env *env);
int		str_check(char *str1, char *str2);
int		char_check(char *str, char c);
t_env	*create_env_var(const char *name, const char *value);

#endif
