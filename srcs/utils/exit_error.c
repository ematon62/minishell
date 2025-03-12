/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ematon <ematon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 13:36:22 by ematon            #+#    #+#             */
/*   Updated: 2025/03/12 13:51:07 by ematon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	exit_error(char *s)
{
	perror(s);
	exit(EXIT_FAILURE);
}

int	check_invalid_path(char *path, t_cmd *cmd, t_shell *sh)
{
	if (!path)
	{
		if (ft_strchr(cmd->args[0], '/'))
			return (ft_putstr_fd(cmd->args[0], STDERR_FILENO),
				ft_putstr_fd(": No such file or directory\n", STDERR_FILENO),
				free_sh_cmds(sh), 127);
		return (ft_putstr_fd(cmd->args[0], STDERR_FILENO),
			ft_putstr_fd(": command not found\n", STDERR_FILENO),
			free_sh_cmds(sh), 127);
	}
	if (is_directory(path))
		return (ft_putstr_fd(cmd->args[0], STDERR_FILENO),
			ft_putstr_fd(": Is a directory\n", STDERR_FILENO),
			free_sh_cmds(sh), 126);
	if (access(path, X_OK))
		return (ft_putstr_fd(cmd->args[0], STDERR_FILENO),
			ft_putstr_fd(": Permission denied\n", STDERR_FILENO),
			free_sh_cmds(sh), 126);
	return (0);
}
