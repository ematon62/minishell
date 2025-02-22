/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ematon <ematon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 13:39:44 by ematon            #+#    #+#             */
/*   Updated: 2025/02/15 11:07:07 by ematon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "libft.h"
# include "structs.h"

void		exit_error(char *s);
t_env_lst	*lst_env_new(char *key, char *value);
void		free_shell(t_shell *shell);

#endif