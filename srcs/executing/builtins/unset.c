/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ematon <ematon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:27:32 by adcisse           #+#    #+#             */
/*   Updated: 2025/03/07 19:50:58 by ematon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"

int	builtin_unset(char **args, t_shell *sh)
{
	int	i;

	i = 0;
	while (args[++i])
		remove_env_var(&sh->env, args[i]);
	return (0);
}

