

#include "../../includes/executing.h"

void	print_redir_error(char *file)
{
	ft_putstr_fd("bash: ", STDERR_FILENO);
	ft_putstr_fd(file, STDERR_FILENO);
	ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
}

void	process_heredocs(t_redirections *r, t_shell *sh)
{
	while (r)
	{
		if (r->type == IS_HEREDOC)
			handle_heredoc(r->target, sh);
		r = r->next;
	}
}

void	create_output_files(t_redirections *r, t_redirections **last_output)
{
	int fd;
	int flags;

	while (r)
	{
		if (r->type == IS_TRUNCAT || r->type == IS_APPEND)
		{
			if (r->type == IS_TRUNCAT)
				flags = O_WRONLY | O_CREAT | O_TRUNC; // Troncature pour >
			else
				flags = O_WRONLY | O_CREAT | O_APPEND; // Ajout pour >>
			fd = open(r->target, flags, 0644);
			if (fd < 0)
				perror("open");
			else
				close(fd);
			*last_output = r; // Dernière redirection de sortie
		}
		r = r->next;
	}
}

t_redirections	*find_last_input_file(t_redirections *r, int *error, char **err_file)
{
	t_redirections *last_input = NULL;
	int fd;

	while (r)
	{
		if (r->type == IS_INREDIR) // Ne traite que les <, pas les <<
		{
			fd = open(r->target, O_RDONLY);
			if (fd < 0)
			{
				*err_file = r->target;
				*error = 1;
				return (last_input); // Arrête à la première erreur
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
