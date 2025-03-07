/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cisse <cisse@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:26:31 by adcisse           #+#    #+#             */
/*   Updated: 2025/03/07 09:06:14 by cisse            ###   ########.fr       */
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

static void	heredoc_sigint(int sig)
{
	(void)sig;
	g_signal = 130;
	close(STDIN_FILENO);
}

static bool	add_line_and_free(int fd, t_shell *sh, char *delim)
{
	char	*line;
	char	*tmp;

	signal(SIGINT, heredoc_sigint);
	signal(SIGQUIT, SIG_IGN);
	line = readline("> ");
	if ((!line || ft_strncmp(line, delim, ft_strlen(delim) + 1) == 0))
	{
		if (!line && !((g_signal == 130) || (g_signal == 131)))
			write(2, "warning: here-doc delimited by end-of-file\n", 43);
		free(line);
		return (true);
	}
	tmp = expand_var(line, sh);
	if (tmp)
		ft_putendl_fd(tmp, fd);
	free(tmp);
	return (false);
}

int	handle_heredoc(char *delim, t_shell *sh, char *heredoc_file)
{
	int		fd;

	fd = open(heredoc_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return (perror("open"), 1);
	signal(SIGINT, heredoc_sigint);
	signal(SIGQUIT, SIG_IGN);
	while (!g_signal)
	{
		if (add_line_and_free(fd, sh, delim))
			break ;
	}
	close(fd);
	if (g_signal == 130)
		return (unlink(heredoc_file), 10);
	return (close(fd));
}
