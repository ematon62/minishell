/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ematon <ematon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 10:39:37 by ematon            #+#    #+#             */
/*   Updated: 2025/02/17 17:44:01 by ematon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	free_tokens_lst(t_token_lst *tokens)
{
	t_token_lst	*temp;

	while (tokens)
	{
		temp = tokens->next;
		if (tokens->token)
			free(tokens->token);
		free(tokens);
		tokens = temp;
	}
}

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
		free_env_vars(shell->env);
		free(shell);
	}
}
