/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cisse <cisse@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:33:04 by adcisse           #+#    #+#             */
/*   Updated: 2025/02/19 23:44:55 by cisse            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/executing.h"

int	is_valid_env_key(char *key)
{
	int	i;

	if (!ft_isalpha(key[0]) && key[0] != '_')
		return (0);
	i = 0;
	while (key[++i])
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (0);
	return (1);
}

void	append_env_var(t_env_lst **env, t_env_lst *new)
{
	t_env_lst	*current;

	if (!*env)
	{
		*env = new;
		return ;
	}
	current = *env;
	while (current->next)
		current = current->next;
	current->next = new;
}


void	add_env_var_end(t_env_lst **env, char *key, char *value)
{
	t_env_lst	*new;

	new = malloc(sizeof(t_env_lst));
	if (!new)
		return ;
	new->key = ft_strdup(key);
	new->value = NULL;
	new->is_env = false;
	if (!new->key)
		return (free(new->key), free(new));
	if (value)
	{
		new->value = ft_strdup(value);
		if (!new->value)
			return (free(new->value), free(new->key), free(new));
		new->is_env = true;
	}
	new->next = NULL;
	append_env_var(env, new);
}

void	update_env_var(t_env_lst **env, char *key, char *value)
{
	t_env_lst	*current;

	current = *env;
	while (current)
	{
		if (ft_strncmp(current->key, key, ft_strlen(key) + 1) == 0)
		{
			if (value)
			{
				free(current->value);
				current->value = ft_strdup(value);
			}
			return ;
		}
		current = current->next;
	}
	add_env_var_end(env, key, value);
}

void	remove_env_var(t_env_lst **env, char *key)
{
	t_env_lst	*current;
	t_env_lst	*prev;

	if (!env || !*env || !key)
		return ;
	current = *env;
	prev = NULL;
	while (current)
	{
		if (ft_strncmp(current->key, key, ft_strlen(key) + 1) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				*env = current->next;
			free(current->key);
			if (current->value)
				free(current->value);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}
