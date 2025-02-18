/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adcisse <adcisse@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-18 15:32:52 by adcisse           #+#    #+#             */
/*   Updated: 2025-02-18 15:32:52 by adcisse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/executing.h"

int	builtin_cd(char **args, t_shell *sh)
{
	char	*path;
	char	cwd[PATH_MAX];
	char	*oldpwd;

	oldpwd = get_env_value(sh->env, "PWD");
	if (!oldpwd)
		oldpwd = ft_strdup("");
	if (!args[1] || ft_strncmp(args[1], "~", 2) == 0)
		path = get_env_value(sh->env, "HOME");
	else
		path = args[1];
	if (!path || chdir(path) != 0)
		return (ft_putstr_fd("cd: invalid path\n", STDERR_FILENO), 1);
	getcwd(cwd, PATH_MAX);
	update_env_var(&sh->env, "OLDPWD", oldpwd);
	update_env_var(&sh->env, "PWD", cwd);
	return (0);
}

// static void	print_env(t_env_lst *env, const char *key)
// {
// 	char	*value;

// 	value = get_env_value(env, key);
// 	printf("%s=%s\n", key, value);
// 	free(value);
// }

// void	free_env(t_env_lst *env)
// {
// 	t_env_lst	*tmp;

// 	while (env)
// 	{
// 		tmp = env;
// 		env = env->next;
// 		free(tmp->key);
// 		free(tmp->value);
// 		free(tmp);
// 	}
// }

// int	main(void)
// {
// 	t_shell	shell;
// 	char	cwd[PATH_MAX];
// 	char	*args[3];

// 	shell = (t_shell){0};
// 	update_env_var(&shell.env, "HOME", getenv("HOME"));
// 	getcwd(cwd, sizeof(cwd));
// 	update_env_var(&shell.env, "PWD", cwd);
// 	update_env_var(&shell.env, "OLDPWD", "");

// 	printf("=== Test 1: cd sans arguments (doit aller à HOME) ===\n");
// 	args[0] = "cd";
// 	args[1] = NULL;
// 	builtin_cd(args, &shell);
// 	print_env(shell.env, "PWD");
// 	print_env(shell.env, "OLDPWD");

// 	printf("\n=== Test 2: cd ~ (doit aller à HOME) ===\n");
// 	args[1] = "~";
// 	args[2] = NULL;
// 	builtin_cd(args, &shell);
// 	print_env(shell.env, "PWD");
// 	print_env(shell.env, "OLDPWD");

// 	printf("\n=== Test 3: cd - (sans ancien PWD) ===\n");
// 	args[1] = "-";
// 	builtin_cd(args, &shell);
// 	print_env(shell.env, "PWD");

// 	printf("\n=== Test 4: cd /tmp ===\n");
// 	args[1] = "/tmp";
// 	builtin_cd(args, &shell);
// 	print_env(shell.env, "PWD");
// 	print_env(shell.env, "OLDPWD");

// 	printf("\n=== Test 6: cd chemin_invalide ===\n");
// 	args[1] = "/chemin/inexistant";
// 	int ret = builtin_cd(args, &shell);
// 	printf("Code retour: %d\n", ret);

// 	// Nettoyage
// 	free_env(shell.env);
// 	return (0);
// }
