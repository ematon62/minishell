/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ematon <ematon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 11:27:10 by adcisse           #+#    #+#             */
/*   Updated: 2025/03/07 15:30:41 by ematon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"

int	count_env_vars(t_env_lst *env)
{
	int	count;

	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}

char	*create_env_entry(t_env_lst *env)
{
	char	*var;
	char	*entry;

	var = ft_strjoin(env->key, "=");
	if (!var)
		return (NULL);
	if (env->value)
		entry = ft_strjoin(var, env->value);
	else
		entry = ft_strjoin(var, "");
	free(var);
	return (entry);
}

char	**env_to_array(t_env_lst *env)
{
	char		**env_arr;
	t_env_lst	*current;
	int			count;
	int			i;

	count = count_env_vars(env);
	env_arr = malloc(sizeof(char *) * (count + 1));
	if (!env_arr)
		return (ft_free_toodee((void **)env_arr), NULL);
	i = 0;
	current = env;
	while (current)
	{
		env_arr[i] = create_env_entry(current);
		if (!env_arr[i])
			return (ft_free_toodee((void **)env_arr), NULL);
		i++;
		current = current->next;
	}
	env_arr[i] = NULL;
	return (env_arr);
}

void	free_array(char **env_arr)
{
	int	i;

	if (!env_arr)
		return ;
	i = 0;
	while (env_arr[i])
	{
		free(env_arr[i]);
		i++;
	}
	free(env_arr);
}
