/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 18:14:16 by yuboktae          #+#    #+#             */
/*   Updated: 2023/10/10 13:49:32 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "struct.h"

void		create_args(t_parse_list *parse_list, t_arg *arg);
int			handle_redirections(t_parse_list *parse_list, t_here_doc *here_doc,
				int *fd_in, int *fd_out);
void		cmd_execution(t_parse_list *parse_list, t_table *main);
void		one_builtin(t_parse_list *parse_list, t_table *main,
				t_cmd_info *cmd_info);		
void		ft_free_str_array(char **str);
char		**ft_split_ignore_spaces(const char *s, char c);
char		*get_executable_path(const char *cmd, const char *path);
char		*ft_strjoin_free(char *s1, char const *s2, int free_s1);
int			one_cmd_exec(t_parse_list *parse_list, t_table *main,
				t_cmd_info *cmd_info);
char		*get_path_from_envp(t_env *env);
void		open_heredoc(t_table *main, t_parse_list *parse_list);
void		add_back_heredoc(t_here_doc *here_doc, int fd);
t_here_doc	*free_n_close_heredoc(t_here_doc **head, int fd);
int			multi_cmds_exec(t_parse_list *parse_list, t_table *main,
				t_cmd_info *cmd_info);
void		ft_close(int fd);
void		close_fd_cmd(t_cmd_info *cmd_info);
int			wait_all_pid(t_cmd_info *cmd_info, pid_t pid);
void		reset_cmd_info(t_cmd_info *cmd_info);
void		check_fd_in(t_redir *file, int *fd_in);
void		check_fd_out(t_redir *file, int *fd_out);
void		file_next(t_redir **file, int *fd);
int			exec_cmd(t_parse_list *parse_list, t_cmd_info *cmd_info,
				t_table *main);
int			handle_io_redir(t_parse_list *s, t_table *main,
				t_cmd_info *cmd_info);
void		if_only_redir(t_parse_list *parse_list, t_table *main,
				int *tmp_fd);		
int			if_exec_path(t_parse_list *s, t_table *main, t_cmd_info *cmd_info);
void		close_cmd_fd(t_cmd_info *cmd_info, int *fdc);
void		dup_and_close(t_parse_list *s, t_cmd_info *cmd_info, int *fdc);
void		ft_child(t_parse_list *parse_list, const char *path,
				t_table *main, int *fdc);
void		execute_child(t_table *main, t_cmd_info *cmd_info, int *fdc,
				const char *path);

#endif
