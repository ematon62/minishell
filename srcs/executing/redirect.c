/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ematon <ematon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 13:20:55 by adcisse           #+#    #+#             */
/*   Updated: 2025/03/05 17:22:08 by ematon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"

static void	redirect_input(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		perror("open");
		return ;
	}
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		perror("dup2");
		close(fd);
		return ;
	}
	close(fd);
}

static void	redirect_output(char *file, int flags)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | flags, 0644);
	if (fd < 0)
	{
		perror("open");
		return ;
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		perror("dup2");
		close(fd);
		return ;
	}
	close(fd);
}

static void	handle_output_redir(t_redirections *r, int *output_done)
{
	if (r->type == IS_TRUNCAT)
		redirect_output(r->target, O_TRUNC);
	else if (r->type == IS_APPEND)
		redirect_output(r->target, O_APPEND);
	*output_done = 1;
}

static void	apply_redirections(t_redirections *r, t_redirections *last_input,
	t_redirections *last_output, t_redir_state *state)
{
	while (r)
	{
		if (r == last_input && !state->input_done)
		{
			redirect_input(r->target);
			state->input_done = 1;
		}
		else if (r == last_output && !state->output_done)
		{
			handle_output_redir(r, &state->output_done);
			state->output_done = 1;
		}
		r = r->next;
	}
}

int	handle_redirections(t_redirections *r)
{
	t_redir_state	state;
	t_redirections	*last_output;
	t_redirections	*last_input;
	int				error;
	char			*err_file;

	state.input_done = 0;
	state.output_done = 0;
	last_output = NULL;
	error = 0;
	err_file = NULL;
	last_input = find_last_input_file(r, &error, &err_file);
	create_output_files(r, &last_output);
	if (error)
	{
		print_redir_error(err_file);
		return (1);
	}
	apply_redirections(r, last_input, last_output, &state);
	return (0);
}
