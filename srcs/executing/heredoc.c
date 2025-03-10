/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ematon <ematon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:26:31 by adcisse           #+#    #+#             */
/*   Updated: 2025/03/10 15:46:35 by ematon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"

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

int	handle_heredoc(char *delim, t_shell *sh, char *hdfile)
{
	int		fd;

	fd = open(hdfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return (perror("open"), 1);
	signal(SIGINT, heredoc_sigint);
	while (!g_signal)
	{
		if (add_line_and_free(fd, sh, delim))
			break ;
	}
	close(fd);
	if (g_signal == 130)
		return (unlink(hdfile), cleanup_heredoc_files(sh->cmds),
			free(hdfile), sh->exit_status = 130, 10);
	return (close(fd));
}

int	process_heredocs(t_redirections *r, t_shell *sh, char *hdfile)
{
	g_signal = 0;
	while (r)
	{
		if (r->type == IS_HEREDOC)
		{
			if (handle_heredoc(r->target, sh, hdfile) == 10)
				return (10);
			r->type = IS_HEREDOC;
			free(r->target);
			r->target = ft_strdup(hdfile);
			if (!r->target)
				return (1);
		}
		r = r->next;
	}
	g_signal = 1;
	return (0);
}

int	pre_process_heredocs(t_cmds *cmds, t_shell *sh)
{
	t_cmds	*current;
	int		i;
	char	*hdfile;
	char	*itoa;

	current = cmds;
	i = 0;
	while (current)
	{
		itoa = ft_itoa(i);
		if (!itoa)
			return (free_cmds(cmds), free_shell(sh),
				exit_error("malloc"), 1);
		hdfile = ft_strjoin(HEREDOC_FILE, itoa);
		if (!hdfile)
			return (free_cmds(cmds), free_shell(sh),
				free(itoa), exit_error("malloc"), 1);
		free(itoa);
		if (process_heredocs(current->cmd->redirs, sh, hdfile) == 10)
			return (10);
		free(hdfile);
		i++;
		current = current->next;
	}
	return (0);
}
