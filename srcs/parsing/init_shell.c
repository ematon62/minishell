/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ematon <ematon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 18:39:38 by ematon            #+#    #+#             */
/*   Updated: 2025/02/17 08:26:44 by ematon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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
			exit_error("malloc");
		new = lst_env_new(split[0], split[1]);
		if (!new)
			return (ft_free_toodee((void **)split), exit_error("malloc"), NULL);
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
		exit_error("malloc");
	shell->cmds = NULL;
	shell->env = NULL;
	shell->exit_status = -1;
	shell->env = get_env_vars(envp);
	return (shell);
}
