/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_and_wait.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ematon <ematon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 11:13:34 by adcisse           #+#    #+#             */
/*   Updated: 2025/03/12 13:27:13 by ematon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"

void	print_redir_error(char *file)
{
	ft_putstr_fd(file, STDERR_FILENO);
	ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
}

int	create_output_files(t_redirections *r, t_redirections **last_output,
	char **err_file, int *error)
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
			{
				*error = 1;
				*err_file = r->target;
				return (1);
			}
			else
				close(fd);
			*last_output = r;
		}
		r = r->next;
	}
	return (0);
}

t_redirections	*find_last_input_file(t_redirections *r, int *error)
{
	t_redirections	*last_input;

	last_input = NULL;
	while (r)
	{
		if (r->type == IS_INREDIR || r->type == IS_HEREDOC)
		{
			if (access(r->target, F_OK))
			{
				*error = 1;
				return (print_redir_error(r->target), last_input);
			}
			else if (access(r->target, R_OK))
			{
				*error = 1;
				return (ft_putstr_fd(r->target, STDERR_FILENO),
					ft_putstr_fd(": Permission denied\n", STDERR_FILENO),
					last_input);
			}
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
