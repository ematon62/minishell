/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cisse <cisse@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 19:39:53 by ematon            #+#    #+#             */
/*   Updated: 2025/02/18 00:54:37 by cisse            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>
#include <errno.h>
#include <linux/limits.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../libft/libft.h"
#include "structs.h"
#include "utils.h"
#include "parsing.h"

#define BUFFER_SIZE 1024
#define HEREDOC_FILE "/tmp/heredoc"
#define WRITE_END 1
#define READ_END 0
#define ERROR 1
#define SUCCESS 0

/* Execution */
void		execute(t_cmds *cmds, t_shell *shell);
void		exec_external(t_cmd *cmd, t_shell *shell);
void		handle_redirections(t_redirections *redirs, t_shell *sh);
int			exec_builtin(t_cmd *cmd, t_shell *shell);
int			is_builtin(char *cmd);
char		*build_path(char *old_path, char *cmd);
char		*find_executable(char *cmd, char **paths);
void		handle_heredoc(char *delim, t_shell *sh);
int			wait_children(pid_t last_pid, int *status);

/* Execution utils*/
void		close_pipes(int fd_in, int fd[2]);
void		close_and_swap(int *fd_in, int fd[2]);
void		save_stdio(int std_copy[2]);
void		restore_stdio(int std_copy[2]);

/* Builtins */
int			builtin_echo(char **args);
int			builtin_cd(char **args, t_shell *shell);
int			builtin_pwd(void);
int			builtin_env(t_env_lst *env);
int			builtin_export(char **args, t_shell *shell);
int			builtin_unset(char **args, t_shell *shell);
int			builtin_exit(char **args, t_shell *shell);

/* Builtins utils*/
int			is_valid_env_key(char *key);
void		update_env_var(t_env_lst **env, char *key, char *value);
char		*get_env_value(t_env_lst *env, const char *key);
void		remove_env_var(t_env_lst **env, char *key);
char		*expand_var(char *token, t_shell *shell);
