


#include "../../includes/executing.h"


void	close_pipes(int fd_in, int fd[2])
{
	if (fd_in != STDIN_FILENO)
		close(fd_in);
	if (fd[0] != -1)
		close(fd[0]);
	if (fd[1] != -1)
		close(fd[1]);
}

void	close_and_swap(int *fd_in, int fd[2])
{
	close(fd[1]);
	*fd_in = fd[0];
}

void	save_stdio(int std_copy[2])
{
	std_copy[0] = dup(STDIN_FILENO);
	std_copy[1] = dup(STDOUT_FILENO);
}

void	restore_stdio(int std_copy[2])
{
	dup2(std_copy[0], STDIN_FILENO);
	dup2(std_copy[1], STDOUT_FILENO);
	close(std_copy[0]);
	close(std_copy[1]);
}

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (!(ft_strcmp(cmd, "echo")) || !(ft_strcmp(cmd, "cd")))
		return (1);
	if (!(ft_strcmp(cmd, "pwd")) || !(ft_strcmp(cmd, "export")))
		return (1);
	if (!(ft_strcmp(cmd, "unset")) || !(ft_strcmp(cmd, "env")))
		return (1);
	if (!(ft_strcmp(cmd, "exit")))
		return (1);
	return (0);
}
