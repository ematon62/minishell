/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ematon <ematon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:32:52 by adcisse           #+#    #+#             */
/*   Updated: 2025/03/07 16:52:10 by ematon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"

static bool	check_path(char *path)
{
	struct stat	path_stat;

	stat(path, &path_stat);
	if (access(path, F_OK))
		return (ft_putstr_fd("cd: No such file or directory\n", 2), 1);
	if (!S_ISDIR(path_stat.st_mode))
		return (ft_putstr_fd("cd: Not a directory\n", STDERR_FILENO), 1);
	if (access(path, X_OK))
		return (ft_putstr_fd("cd: ", 2), ft_putstr_fd(path, 2),
			ft_putstr_fd(": Permission denied\n", 2), 1);
	return (0);
}

int	builtin_cd(char **args, t_shell *sh)
{
	char		cwd[PATH_MAX];

	if (!args[1])
		return (ft_putstr_fd("cd: invalid arguments\n", STDERR_FILENO), 1);
	if (!args[1][0])
		return (0);
	if (args[2])
		return (ft_putstr_fd("cd: too many arguments\n", STDERR_FILENO), 1);
	if (check_path(args[1]))
		return (1);
	if (!getcwd(cwd, PATH_MAX))
		return (perror("getcwd"), 1);
	update_env_var(&sh->env, "OLDPWD", cwd);
	if (chdir(args[1]) != 0)
		return (perror("chdir"), 1);
	if (!getcwd(cwd, PATH_MAX))
		return (perror("getcwd"), 1);
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
