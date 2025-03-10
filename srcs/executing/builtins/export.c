/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ematon <ematon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:28:06 by adcisse           #+#    #+#             */
/*   Updated: 2025/03/10 17:16:04 by ematon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"

static void	print_export(t_env_lst *env)
{
	while (env)
	{
		if (env->value)
			printf("declare -x %s=\"%s\"\n", env->key, env->value);
		else
			printf("declare -x %s\n", env->key);
		env = env->next;
	}
}

static char	*get_key(char *arg, char *eq)
{
	if (eq)
		return (ft_substr(arg, 0, eq - arg));
	else
		return (ft_strdup(arg));
}

static char	*get_value(char *eq)
{
	if (eq)
		return (ft_strdup(eq + 1));
	else
		return (NULL);
}

int	builtin_export(char **args, t_shell *sh)
{
	char	*eq;
	char	*key;
	char	*val;
	int		ret;

	ret = 0;
	if (!args[1])
		return (print_export(sh->env), EXIT_SUCCESS);
	args++;
	while (*args)
	{
		eq = ft_strchr(*args, '=');
		key = get_key(*args, eq);
		val = get_value(eq);
		if (!is_valid_env_key(key))
		{
			ft_putstr_fd("export: invalid identifier\n", STDERR_FILENO);
			ret = EXIT_FAILURE;
		}
		else
			update_env_var(&sh->env, key, val);
		free(key);
		args++;
	}
	return (ret);
}
