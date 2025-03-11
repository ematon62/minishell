/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_and_wait.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ematon <ematon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 11:13:34 by adcisse           #+#    #+#             */
/*   Updated: 2025/03/11 16:07:34 by ematon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"

void	print_redir_error(char *file)
{
	ft_putstr_fd(file, STDERR_FILENO);
	ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
}

void	create_output_files(t_redirections *r, t_redirections **last_output)
{
	int	fd;
	int	flags;

	while (r)
	{
		if (r->type == IS_TRUNCAT || r->type == IS_APPEND)
		{
			if (r->type == IS_TRUNCAT)
				flags = O_WRONLY | O_CREAT | O_TRUNC;
			else
				flags = O_WRONLY | O_CREAT | O_APPEND;
			fd = open(r->target, flags, 0644);
			if (fd < 0)
				perror("open");
			else
				close(fd);
			*last_output = r;
		}
		r = r->next;
	}
}

t_redirections	*find_last_input_file(t_redirections *r, int *error,
				char **err_file)
{
	t_redirections	*last_input;
	int				fd;

	last_input = NULL;
	while (r)
	{
		if (r->type == IS_INREDIR || r->type == IS_HEREDOC)
		{
			fd = open(r->target, O_RDONLY);
			if (fd < 0)
			{
				*err_file = r->target;
				*error = 1;
				return (last_input);
			}
			close(fd);
			last_input = r;
		}
		r = r->next;
	}
	return (last_input);
}

int	wait_children(pid_t last_pid, int *status, t_shell *sh)
{
	pid_t	pid;
	int		sig;

	pid = waitpid(-1, status, WUNTRACED);
	while (pid > 0)
	{
		if (pid == last_pid)
		{
			if (WIFEXITED(*status))
				sh->exit_status = WEXITSTATUS(*status);
			else if (WIFSIGNALED(*status))
			{
				sig = WTERMSIG(*status);
				if (sig == SIGINT)
					sh->exit_status = 130;
				else if (sig == SIGQUIT)
					sh->exit_status = 131;
			}
		}
		pid = waitpid(-1, status, WUNTRACED);
	}
	g_signal = 0;
	return (sh->exit_status);
}
