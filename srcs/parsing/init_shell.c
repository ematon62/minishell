/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ematon <ematon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 18:39:38 by ematon            #+#    #+#             */
/*   Updated: 2025/03/10 15:19:12 by ematon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_env_lst	*new_var(char *env_var)
{
	int			j;
	char		*key;
	char		*value;

	j = 0;
	while (env_var[j] && env_var[j] != '=')
		j++;
	key = ft_substr(env_var, 0, j);
	if (!key)
		return (NULL);
	value = ft_substr(env_var, j + 1, ft_strlen(env_var));
	if (!value)
		return (free(key), NULL);
	return (lst_env_new(key, value));
}

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

	i = 0;
	current = NULL;
	while (envp && envp[i])
	{
		new = new_var(envp[i]);
		if (!new)
			return (free_env_vars(current), NULL);
		ft_lstadd_back((t_list **)&current, (t_list *)new);
		i++;
	}
	return (current);
}

t_shell	*init_shell(char **envp, int argc, char **argv)
{
	t_shell	*shell;

	(void)argc;
	(void)argv;
	shell = malloc(sizeof(t_shell));
	if (!shell)
		exit_error("malloc");
	shell->cmds = NULL;
	shell->env = NULL;
	shell->exit_status = 0;
	shell->env = get_env_vars(envp);
	return (shell);
}
