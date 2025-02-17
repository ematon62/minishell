/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ematon <ematon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 13:39:44 by ematon            #+#    #+#             */
/*   Updated: 2025/02/17 12:57:42 by ematon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "libft.h"
# include "structs.h"

//Gestion d'erreur
void		exit_error(char *s);

//Listes chainees
t_env_lst	*lst_env_new(char *key, char *value);
t_token_lst	*token_lst_new(t_token type, char *token);

//Gestion de mémoire
void		free_shell(t_shell *shell);

#endif