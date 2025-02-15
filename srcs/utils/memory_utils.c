/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ematon <ematon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 10:39:37 by ematon            #+#    #+#             */
/*   Updated: 2025/02/15 13:45:57 by ematon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	free_shell(t_shell *shell)
{
	t_env_lst	*current;
	t_env_lst	*temp;

	if (shell)
	{
		if (shell->path)
			ft_free_toodee((void **)shell->path);
		current = shell->env;
		while (current)
		{
			temp = current->next;
			free(current->key);
			free(current->value);
			free(current);
			current = temp;
		}
		free(shell);
	}
}
