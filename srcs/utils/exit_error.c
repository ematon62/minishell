/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ematon <ematon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 13:36:22 by ematon            #+#    #+#             */
/*   Updated: 2025/03/11 16:18:09 by ematon           ###   ########.fr       */
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
			return (printf("%s: No such file or directory\n", cmd->args[0]),
				free_sh_cmds(sh), 127);
		return (printf("%s: command not found\n", cmd->args[0]),
			free_sh_cmds(sh), 127);
	}
	if (is_directory(path))
		return (printf("%s: Is a directory\n", cmd->args[0]),
			free_sh_cmds(sh), 126);
	if (access(path, X_OK))
		return (printf("%s: Permission denied\n", cmd->args[0]),
			free_sh_cmds(sh), 126);
	return (0);
}
