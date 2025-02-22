/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adcisse <adcisse@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-18 15:26:31 by adcisse           #+#    #+#             */
/*   Updated: 2025-02-18 15:26:31 by adcisse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executing.h"

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
		if ((access(cmd, X_OK) == 0))
			return (strdup(cmd));
		return (NULL);
	}
	while (*paths)
	{
		path = build_path(*paths, cmd);
		if (path && (access(path, X_OK) == 0))
			return (path);
		free(path);
		paths++;
	}
	return (NULL);
}

void	handle_heredoc(char *delim, t_shell *sh)
{
	int		fd;
	char	*line;
	char	*tmp;

	fd = open(HEREDOC_FILE, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return (perror("heredoc"));
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strncmp(line, delim, ft_strlen(delim) + 1) == 0)
		{
			write(2, "warning: here-doc delimited by end-of-file\n", 43);
			break ;
		}
		tmp = expand_var(line, sh->env);
		ft_putendl_fd(tmp, fd);
		free(line);
		free(tmp);
	}
	close(fd);
	fd = open(HEREDOC_FILE, O_RDONLY);
	unlink(HEREDOC_FILE);
	dup2(fd, STDIN_FILENO);
	close(fd);
}
