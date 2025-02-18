/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adcisse <adcisse@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-18 13:20:55 by adcisse           #+#    #+#             */
/*   Updated: 2025-02-18 13:20:55 by adcisse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executing.h"

static void	redirect_input(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
}

static void	redirect_output(char *file, int flags)
{
	int	fd;

	fd = open(file, flags, 0644);
	if (fd < 0)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	handle_redirections(t_redirections *r, t_shell *sh)
{
	while (r)
	{
		if (r->type == IS_HEREDOC)
			handle_heredoc(r->target, sh);
		else if (r->type == IS_INREDIR)
			redirect_input(r->target);
		else if (r->type == IS_TRUNCAT)
			redirect_output(r->target, O_TRUNC);
		else if (r->type == IS_APPEND)
			redirect_output(r->target, O_APPEND);
		r = r->next;
	}
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
	return (exit_status);
}
