/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adcisse <adcisse@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-18 15:33:04 by adcisse           #+#    #+#             */
/*   Updated: 2025-02-18 15:33:04 by adcisse          ###   ########.fr       */
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

void	update_env_var(t_env_lst **env, char *key, char *value)
{
	t_env_lst	*current;
	t_env_lst *new;

	current = *env;
	while (current)
	{
		if (ft_strncmp(current->key, key, ft_strlen(key) + 1) == 0)
		{
			free(current->value);
			current->value = ft_strdup(value);
			return ;
		}
		current = current->next;
	}
	new = malloc(sizeof(t_env_lst));
	if (!new)
		return ;
	new->key = ft_strdup(key);
	new->value = ft_strdup(value);
	new->next = *env;
	*env = new;
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
