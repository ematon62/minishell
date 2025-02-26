/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cisse <cisse@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:27:22 by adcisse           #+#    #+#             */
/*   Updated: 2025/02/24 22:11:01 by cisse            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	if (fd[1] != -1)
		close(fd[1]);
	if (*fd_in != STDIN_FILENO && *fd_in != -1)
		close(*fd_in);
	*fd_in = fd[0];
}

void	save_stdio(int std_copy[2])
{
	std_copy[0] = dup(STDIN_FILENO);
	std_copy[1] = dup(STDOUT_FILENO);
}

void	restore_stdio(int std_copy[2])
{
	if (std_copy[0] != -1)
		dup2(std_copy[0], STDIN_FILENO);
	close(std_copy[0]);
	if (std_copy[1] != -1)
		dup2(std_copy[1], STDOUT_FILENO);
	close(std_copy[1]);
}

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (!(ft_strncmp(cmd, "echo", 5)) || !(ft_strncmp(cmd, "cd", 3)))
		return (1);
	if (!(ft_strncmp(cmd, "pwd", 4)) || !(ft_strncmp(cmd, "export", 7)))
		return (1);
	if (!(ft_strncmp(cmd, "unset", 6)) || !(ft_strncmp(cmd, "env", 4)))
		return (1);
	if (!(ft_strncmp(cmd, "exit", 5)))
		return (1);
	return (0);
}
