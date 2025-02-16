/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cisse <cisse@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 19:39:53 by ematon            #+#    #+#             */
/*   Updated: 2025/02/16 22:09:30 by cisse            ###   ########.fr       */
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

#define BUFFER_SIZE 1024
#define HEREDOC_FILE "/tmp/heredoc"
#define WRITE_END 1
#define READ_END 0
#define ERROR 1
#define SUCCESS 0

/* Execution */
void		execute(t_cmds *cmds, t_shell *shell);
void		exec_external(t_cmd *cmd, t_shell *shell);
void		handle_redirections(t_redirections *redirs);
int			exec_builtin(t_cmd *cmd, t_shell *shell);
int         is_builtin(char *cmd);
char        *build_path(char *old_path, char *cmd);
char        *find_executable(char *cmd, char **paths);
void        handle_heredoc(char *delim);

/* Builtins */
int			builtin_echo(char **args);
int			builtin_cd(char **args, t_shell *shell);
int			builtin_pwd(void);
int			builtin_env(t_env_lst *env);
int			builtin_export(char **args, t_shell *shell);
int			builtin_unset(char **args, t_shell *shell);
int			builtin_exit(char **args, t_shell *shell);

/* Builtins utils*/
int         is_valid_env_key(char *key);
void        update_env_var(t_env_lst **env, char *key, char *value);

