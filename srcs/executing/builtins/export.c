/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cisse <cisse@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:28:06 by adcisse           #+#    #+#             */
/*   Updated: 2025/02/19 23:46:57 by cisse            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/executing.h"

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


// int	main(void)
// {
// 	t_shell shell;
// 	char *args1[] = {"export", "a=", "d1", "d2", "d3", NULL};

// 	// Initialisation de l'environnement
// 	shell.env = NULL;
// 	update_env_var(&shell.env, "VAR1", "hello");

// 	// Affichage avant export
// 	printf("🔹 ENV AVANT EXPORT:\n");
// 	print_export(shell.env);

// 	// Test export a=1 2 3
// 	printf("\n🚀 Test: export a=1 2 3\n");
// 	builtin_export(args1, &shell);

// 	// Affichage après export
// 	printf("\n🔹 ENV APRÈS EXPORT:\n");
// 	print_export(shell.env);

// 	// Libération de l'environnement
// 	while (shell.env)
// 	{
// 		t_env_lst *tmp = shell.env;
// 		shell.env = shell.env->next;
// 		free(tmp->key);
// 		free(tmp->value);
// 		free(tmp);
// 	}

// 	return (0);
// }

// int	main(void)
// {
// 	t_shell shell;
// 	char *args1[] = {"export", "VAR3=hello", NULL};
// 	char *args2[] = {"export", "VAR2=newvalue", NULL};
// 	char *args3[] = {"export", "INVALID-VAR=value", NULL};

// 	// Initialisation de l'environnement
// 	shell.env = NULL;
// 	update_env_var(&shell.env, "VAR1", "hello");
// 	update_env_var(&shell.env, "VAR2", "world");

// 	// Affichage avant export
// 	printf("🔹 ENV AVANT EXPORT:\n");
// 	print_export(shell.env);

// 	// Test export VAR3 (nouvelle variable)
// 	printf("\n🚀 Test: export VAR3=hello\n");
// 	builtin_export(args1, &shell);
// 	print_export(shell.env);

// 	// Test export VAR2 (mise à jour)
// 	printf("\n🚀 Test: export VAR2=newvalue\n");
// 	builtin_export(args2, &shell);
// 	print_export(shell.env);

// 	// Test export avec une clé invalide
// 	printf("\n🚀 Test: export INVALID-VAR=value\n");
// 	builtin_export(args3, &shell);
// 	print_export(shell.env);

// 	// Libération de l'environnement
// 	while (shell.env)
// 	{
// 		t_env_lst *tmp = shell.env;
// 		shell.env = shell.env->next;
// 		free(tmp->key);
// 		free(tmp->value);
// 		free(tmp);
// 	}

// 	return (0);
// } // cc -Wall -Wextra -Werror -I../../../libft -L../../../libft -g export.c builtins_utils.c  -lft
