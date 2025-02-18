/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adcisse <adcisse@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-18 15:27:32 by adcisse           #+#    #+#             */
/*   Updated: 2025-02-18 15:27:32 by adcisse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/executing.h"

int	builtin_unset(char **args, t_shell *sh)
{
	int	i;
	int	ret;

	ret = 0;
	i = 0;
	while (args[++i])
	{
		if (!is_valid_env_key(args[i]))
		{
			ft_putstr_fd("unset: invalid identifier\n", STDERR_FILENO);
			ret = 1;
			continue ;
		}
		remove_env_var(&sh->env, args[i]);
	}
	return (ret);
}
