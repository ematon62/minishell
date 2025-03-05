/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ematon <ematon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 19:39:53 by ematon            #+#    #+#             */
/*   Updated: 2025/03/05 17:58:46 by ematon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "utils.h"

#define BUFFER_SIZE 1024
#define HEREDOC_FILE "/tmp/heredoc"
#define WRITE_END 1
#define READ_END 0
#define ERROR 1
#define SUCCESS 0

/* Signals */
extern volatile sig_atomic_t	g_signal;

void			setup_signals(void);

/* Execution */
void			execute(t_cmds *cmds, t_shell *shell);
void			exec_external(t_cmd *cmd, t_shell *shell);
int				handle_redirections(t_redirections *redirs);
int				exec_builtin(t_cmd *cmd, t_shell *shell);
int				is_builtin(char *cmd);
char			*build_path(char *old_path, char *cmd);
char			*find_executable(char *cmd, char **paths);
int				handle_heredoc(char *delim, t_shell *sh);
int				wait_children(pid_t last_pid, int *status);
int				exec_redir_builtin(t_cmd *cmd, t_shell *sh);

/* Execution utils*/
void			close_pipes(int fd_in, int fd[2]);
void			close_and_swap(int *fd_in, int fd[2]);
void			save_stdio(int std_copy[2]);
void			restore_stdio(int std_copy[2]);
char			**env_to_array(t_env_lst *env);
void			free_array(char **env_arr);
void			free_utils(char *path, char **all_path, char **env_arr);

/* Builtins */
int				builtin_echo(char **args);
int				builtin_cd(char **args, t_shell *shell);
int				builtin_pwd(void);
int				builtin_env(t_env_lst *env);
int				builtin_export(char **args, t_shell *shell);
int				builtin_unset(char **args, t_shell *shell);
int				builtin_exit(char **args, t_shell *shell);

/* Builtins utils*/
int				is_valid_env_key(char *key);
void			update_env_var(t_env_lst **env, char *key, char *value);
char			*get_env_value(t_env_lst *env, const char *key);
void			remove_env_var(t_env_lst **env, char *key);

/* Redirs */
t_redirections	*find_last_input_file(t_redirections *r, int *error,
					char **err_file);
void			create_output_files(t_redirections *r,
					t_redirections **last_output);
int				process_heredocs(t_redirections *r, t_shell *sh);
int				pre_process_heredocs(t_cmds *cmds, t_shell *sh);
void			print_redir_error(char *file);
