/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ematon <ematon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 18:39:38 by ematon            #+#    #+#             */
/*   Updated: 2025/02/27 13:50:34 by ematon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/*
- envp: environment pointer
- Renvoie une liste chainee contenant
les variables heritees de l'environnement
*/
t_env_lst	*get_env_vars(char **envp)
{
	t_env_lst	*current;
	t_env_lst	*new;
	int			i;
	char		**split;

	i = 0;
	current = NULL;
	while (envp && envp[i])
	{
		split = ft_split(envp[i], '=');
		if (!split)
			return (free_env_vars(current), NULL);
		new = lst_env_new(split[0], split[1]);
		if (!new || !new->key || !new->value)
			return (ft_free_toodee((void **)split),
				free_env_vars(current), NULL);
		ft_lstadd_back((t_list **)&current, (t_list *)new);
		ft_free_toodee((void **)split);
		i++;
	}
	return (current);
}

t_shell	*init_shell(char **envp)
{
	t_shell	*shell;

	shell = malloc(sizeof(t_shell));
	if (!shell)
		return (NULL);
	shell->cmds = NULL;
	shell->env = NULL;
	shell->exit_status = 0;
	shell->env = get_env_vars(envp);
	if (!shell->env)
		return (free(shell), NULL);
	return (shell);
}
