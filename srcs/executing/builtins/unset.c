/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adcisse <adcisse@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-18 15:27:32 by adcisse           #+#    #+#             */
/*   Updated: 2025-02-18 15:27:32 by adcisse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/executing.h"

int	builtin_unset(char **args, t_shell *sh)
{
	int	i;
	int	ret;

	ret = 0;
	i = 0;
	while (args[++i])
	{
		if (!is_valid_env_key(args[i]))
		{
			ft_putstr_fd("unset: invalid identifier\n", STDERR_FILENO);
			ret = 1;
			continue ;
		}
		remove_env_var(&sh->env, args[i]);
	}
	return (ret);
}

// void	print_env(t_env_lst *env)
// {
// 	while (env)
// 	{
// 		printf("%s=%s\n", env->key, env->value);
// 		env = env->next;
// 	}
// }

// // Fonction pour ajouter une variable à l'environnement (test)
// void	add_env_var(t_env_lst **env, char *key, char *value)
// {
// 	t_env_lst *new = malloc(sizeof(t_env_lst));
// 	if (!new)
// 		return ;
// 	new->key = strdup(key);
// 	new->value = strdup(value);
// 	new->is_env = true;
// 	new->next = *env;
// 	*env = new;
// }

// int	main(void)
// {
// 	t_shell shell;
// 	char *args1[] = {"unset", "VAR1", NULL};
// 	char *args2[] = {"unset", "INVALID-VAR", NULL};

// 	// Initialisation de l'environnement
// 	shell.env = NULL;
// 	add_env_var(&shell.env, "VAR1", "hello");
// 	add_env_var(&shell.env, "VAR2", "world");
// 	add_env_var(&shell.env, "PATH", "/usr/bin");

// 	// Affichage avant unset
// 	printf("🔹 ENV AVANT UNSET:\n");
// 	print_env(shell.env);

// 	// Test unset avec VAR1 (existe)
// 	printf("\n🚀 Test: unset VAR1\n");
// 	builtin_unset(args1, &shell);
// 	print_env(shell.env);

// 	// Test unset avec une variable invalide
// 	printf("\n🚀 Test: unset INVALID-VAR\n");
// 	builtin_unset(args2, &shell);
// 	print_env(shell.env);

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
