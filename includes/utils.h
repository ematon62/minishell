/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ematon <ematon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 13:39:44 by ematon            #+#    #+#             */
/*   Updated: 2025/02/26 14:41:14 by ematon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "libft.h"
# include "structs.h"

//Gestion d'erreur
void			exit_error(char *s);

//Listes chainees
t_env_lst		*lst_env_new(char *key, char *value);
t_token_lst		*token_lst_new(t_token type, char *token);
t_token_lst		*token_lst_last(t_token_lst *tokens);
t_redirections	*lst_redir_new(t_type type, char *target);

//Gestion de mémoire
void			free_cmds(t_cmds *cmds);
void			free_shell(t_shell *shell);
void			free_redirs(t_redirections *redirs);
void			free_tokens_lst(t_token_lst *tokens);
void			free_env_vars(t_env_lst	*env_vars);

#endif