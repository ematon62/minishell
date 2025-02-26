/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cisse <cisse@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:27:10 by adcisse           #+#    #+#             */
/*   Updated: 2025/02/26 01:04:26 by cisse            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executing.h"

int	exec_builtin(t_cmd *cmd, t_shell *sh)
{
	if (ft_strncmp(cmd->args[0], "echo", 5) == 0)
		return (builtin_echo(cmd->args));
	if (ft_strncmp(cmd->args[0], "cd", 3) == 0)
		return (builtin_cd(cmd->args, sh));
	if (ft_strncmp(cmd->args[0], "pwd", 4) == 0)
		return (builtin_pwd());
	if (ft_strncmp(cmd->args[0], "export", 7) == 0)
		return (builtin_export(cmd->args, sh));
	if (ft_strncmp(cmd->args[0], "unset", 6) == 0)
		return (builtin_unset(cmd->args, sh));
	if (ft_strncmp(cmd->args[0], "env", 4) == 0)
		return (builtin_env(sh->env));
	if (ft_strncmp(cmd->args[0], "exit", 5) == 0)
		return (builtin_exit(cmd->args, sh)); // close fd
	return (0);
}

void	exec_external(t_cmd *cmd, t_shell *sh)
{
	char	*path;
	char	**all_path;
	char	**env_arr;

	path = get_env_value(sh->env, "PATH");
	env_arr = env_to_array(sh->env);
	if (!path ||!env_arr)
		return (free(path), free_array(env_arr));
	all_path = ft_split(path, ':');
	if (!all_path)
		return (free(path), free_array(all_path), free_array(env_arr));
	path = find_executable(cmd->args[0], all_path);
	if (!path)
	{
		printf("%s: command not found\n", cmd->args[0]);
		free_array(env_arr);
		exit(127);
		return (free(path), free_array(all_path), free_array(env_arr), exit(127));
	}
	execve(path, cmd->args, env_arr);
	perror("execve");
	free(path);
	free_array(all_path);
	free_array(env_arr);
	exit(126);
}

static void	exec_child(t_cmds *cmds, t_shell *sh, int fd_in, int fd[2])
{
	t_cmd	*cmd;

	cmd = cmds->cmd;
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	dup2(fd_in, STDIN_FILENO);
	if (cmds->next)
		dup2(fd[1], STDOUT_FILENO);
	close_pipes(fd_in, fd);
	if (handle_redirections(cmd->redirs, sh) != 0)
		exit(1);
	if (is_builtin(cmd->args[0]))
		exit(exec_builtin(cmd, sh));
	else
		exec_external(cmd, sh);
}

static int	exec_pipeline(t_cmds *cmds, t_shell *sh)
{
	int		fd[2];
	int		fd_in;
	pid_t	pid;
	int		status;

	fd_in = dup(STDIN_FILENO);
	while (cmds)
	{
		if (cmds->next && pipe(fd) < 0)
			return (perror("pipe"), ERROR);
		pid = fork();
		if (pid < 0)
			return (perror("fork"), ERROR);
		if (pid == 0)
		{
			exec_child(cmds, sh, fd_in, fd);
			exit(EXIT_FAILURE);
		}
		close_and_swap(&fd_in, fd);
		cmds = cmds->next;
	}
	close(fd_in);
	return (wait_children(pid, &status), status);
}

void	execute(t_cmds *cmds, t_shell *sh)
{
	int		status;
	int		std_copy[2];

	if (!cmds)
		return ;
	save_stdio(std_copy);
	setup_signals();
	g_signal = 1;
	if (!cmds->next && !cmds->cmd->redirs && is_builtin(cmds->cmd->args[0]))
		sh->exit_status = exec_builtin(cmds->cmd, sh);
	else
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		status = exec_pipeline(cmds, sh);
		sh->exit_status = WEXITSTATUS(status);
	}
	g_signal = 0;
	restore_stdio(std_copy);
	setup_signals();
}
