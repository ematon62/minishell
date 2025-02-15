/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ematon <ematon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 10:39:37 by ematon            #+#    #+#             */
/*   Updated: 2025/02/15 19:02:51 by ematon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	free_env_vars(t_env_lst	*env_vars)
{
	t_env_lst	*current;
	t_env_lst	*temp;

	current = env_vars;
	while (current)
	{
		temp = current->next;
		free(current->key);
		free(current->value);
		free(current);
		current = temp;
	}
}

void	free_shell(t_shell *shell)
{
	if (shell)
	{
		if (shell->path)
			ft_free_toodee((void **)shell->path);
		free_env_vars(shell->env);
		free(shell);
	}
}
