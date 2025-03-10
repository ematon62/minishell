/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ematon <ematon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 13:39:44 by ematon            #+#    #+#             */
/*   Updated: 2025/03/10 16:59:43 by ematon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "libft.h"
# include "structs.h"

/* Signals */
extern volatile sig_atomic_t	g_signal;

void			setup_signals(void);
void			heredoc_sigint(int sig);
void			sigint_handler(int sig);
void			child_sigquit(int sig);
void			child_sigint(int sig);

//Gestion d'erreur
void			exit_error(char *s);
bool 			is_directory(char *path);
int				check_invalid_path(char *path, t_cmd *cmd, t_shell *sh);

//Listes chainees
t_env_lst		*lst_env_new(char *key, char *value);
t_token_lst		*token_lst_new(t_token type, char *token);
t_token_lst		*token_lst_last(t_token_lst *tokens);
t_redirections	*lst_redir_new(t_token token_type, char *target);
t_cmds			*lst_new_cmds(t_cmd *cmd);

//Gestion de mémoire
void			free_cmds(t_cmds *cmds);
void			free_shell(t_shell *shell);
void			free_redirs(t_redirections *redirs);
void			free_tokens_lst(t_token_lst *tokens);
void			free_env_vars(t_env_lst	*env_vars);
void			free_sh_cmds(t_shell *shell);
void			free_path_var(char *path, char **all_path, char **env_arr);

//Expansion de variables
char			*expand_var(char *token, t_shell *shell);

#endif