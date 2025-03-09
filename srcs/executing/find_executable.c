/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_executable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ematon <ematon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 18:27:40 by ematon            #+#    #+#             */
/*   Updated: 2025/03/09 21:24:36 by ematon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"

char	*build_path(char *old_path, char *cmd)
{
	char	*path;
	int		path_len;
	int		i;
	int		j;

	if (!old_path || !cmd)
		return (NULL);
	path_len = ft_strlen(old_path) + ft_strlen(cmd);
	path = malloc((path_len + 2) * sizeof(char));
	if (!path)
		return (NULL);
	i = 0;
	j = 0;
	while (old_path[i])
		path[j++] = old_path[i++];
	path[j++] = '/';
	i = 0;
	while (cmd[i])
		path[j++] = cmd[i++];
	path[j] = '\0';
	return (path);
}

char	*find_executable(char *cmd, char **paths)
{
	char	*path;

	if (!cmd || !paths)
		return (NULL);
	if (cmd[0] == '/' || (cmd[0] == '.' && cmd[1] == '/'))
	{
		if ((!access(cmd, F_OK)))
			return (ft_strdup(cmd));
		return (NULL);
	}
	while (*paths)
	{
		path = build_path(*paths, cmd);
		if (path && (!access(path, F_OK)))
			return (path);
		free(path);
		paths++;
	}
	return (NULL);
}
