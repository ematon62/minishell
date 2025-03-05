/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_and_wait.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cisse <cisse@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 11:13:34 by adcisse           #+#    #+#             */
/*   Updated: 2025/03/01 14:21:57 by cisse            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executing.h"

void	print_redir_error(char *file)
{
	ft_putstr_fd("bash: ", STDERR_FILENO);
	ft_putstr_fd(file, STDERR_FILENO);
	ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
}

int	process_heredocs(t_redirections *r, t_shell *sh)
{
	g_signal = 0;
	while (r)
	{
		if (r->type == IS_HEREDOC)
		{
			if(handle_heredoc(r->target, sh) == 10)
				return (10);
			r->type = IS_INREDIR;
			r->target = HEREDOC_FILE;
		}
		r = r->next;
	}
	g_signal = 1;
	return (0);
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
		if (r->type == IS_INREDIR)
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

int	wait_children(pid_t last_pid, int *status)
{
	pid_t	pid;
	int		exit_status;

	exit_status = 0;
	pid = waitpid(-1, status, WUNTRACED);
	while (pid > 0)
	{
		if (pid == last_pid)
		{
			if (WIFEXITED(*status))
				exit_status = WEXITSTATUS(*status);
			else if (WIFSIGNALED(*status))
				exit_status = 128 + WTERMSIG(*status);
		}
		pid = waitpid(-1, status, WUNTRACED);
	}
	g_signal = 0;
	return (exit_status);
}
