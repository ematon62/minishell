/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ematon <ematon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:32:52 by adcisse           #+#    #+#             */
/*   Updated: 2025/03/11 16:03:57 by ematon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"

bool	is_directory(char *path)
{
	struct stat	path_stat;

	stat(path, &path_stat);
	return (S_ISDIR(path_stat.st_mode));
}

bool	check_path(char *path)
{
	if (access(path, F_OK))
		return (ft_putstr_fd("cd: No such file or directory\n", 2), 1);
	if (!is_directory(path))
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
