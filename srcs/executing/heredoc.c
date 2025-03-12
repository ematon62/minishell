/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ematon <ematon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:26:31 by adcisse           #+#    #+#             */
/*   Updated: 2025/03/12 11:16:07 by ematon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"

static bool	add_line_and_free(int fd, t_shell *sh, char *delim)
{
	char	*line;
	char	*tmp;

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

static int	child_heredoc(char *hdfile, t_shell *sh, char *delim, int *cpy)
{
	int	fd;

	fd = open(hdfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return (free(hdfile), cleanup_heredoc_files(sh->cmds),
			free_sh_cmds(sh), exit_error("open"), 1);
	while (!g_signal)
	{
		if (add_line_and_free(fd, sh, delim))
			break ;
	}
	close(fd);
	restore_stdio(cpy);
	if (g_signal == 130)
		return (unlink(hdfile), cleanup_heredoc_files(sh->cmds),
			free_sh_cmds(sh), free(hdfile),
			exit(130), 10);
	return (free(hdfile), free_sh_cmds(sh), exit(EXIT_SUCCESS), 0);
}

static int	this_heredoc(char *delim, t_shell *sh, char *hdfile, int *cpy)
{
	pid_t	pid;
	int		status;

	signal(SIGINT, heredoc_sigint);
	signal(SIGQUIT, SIG_IGN);
	pid = fork();
	if (pid < 0)
		return (cleanup_heredoc_files(sh->cmds), restore_stdio(cpy),
			free(hdfile), free_sh_cmds(sh), exit_error("fork"), 1);
	if (!pid)
		child_heredoc(hdfile, sh, delim, cpy);
	wait_children(pid, &status, sh);
	if (status)
		return (restore_stdio(cpy), 10);
	return (0);
}

static int	process_heredocs(t_redirections *r, t_shell *sh, char *hdfile,
	int *cpy)
{
	g_signal = 0;
	while (r)
	{
		if (r->type == IS_HEREDOC)
		{
			if (this_heredoc(r->target, sh, hdfile, cpy) == 10)
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

int	pre_process_heredocs(t_cmds *cmds, t_shell *sh, int *cpy)
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
			return (free_cmds(cmds), free_shell(sh), restore_stdio(cpy),
				exit_error("malloc"), 1);
		hdfile = ft_strjoin(HEREDOC_FILE, itoa);
		if (!hdfile)
			return (free_cmds(cmds), free_shell(sh), restore_stdio(cpy),
				free(itoa), exit_error("malloc"), 1);
		free(itoa);
		if (process_heredocs(current->cmd->redirs, sh, hdfile, cpy) == 10)
			return (free(hdfile), 10);
		free(hdfile);
		i++;
		current = current->next;
	}
	return (0);
}
