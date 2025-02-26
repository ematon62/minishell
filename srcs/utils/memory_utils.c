/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ematon <ematon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 10:39:37 by ematon            #+#    #+#             */
/*   Updated: 2025/02/26 14:35:47 by ematon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

//Fonctions pour fonctions toutes les structures

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

void	free_redirs(t_redirections *redirs)
{
	t_redirections	*temp;

	while (redirs)
	{
		temp = redirs->next;
		if (redirs->target)
			free(redirs->target);
		free(redirs);
		redirs = temp;
	}
}

void	free_cmds(t_cmds *cmds)
{
	t_cmds	*temp_cmds;

	while (cmds)
	{
		temp_cmds = cmds->next;
		if (cmds->cmd)
		{
			ft_free_toodee((void **)cmds->cmd->args);
			free_redirs(cmds->cmd->redirs);
			free(cmds->cmd);
		}
		free(cmds);
		cmds = temp_cmds;
	}
}

void	free_shell(t_shell *shell)
{
	if (shell)
	{
		free_env_vars(shell->env);
		free_cmds(shell->cmds);
		free(shell);
	}
}
