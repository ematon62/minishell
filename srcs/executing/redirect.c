

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