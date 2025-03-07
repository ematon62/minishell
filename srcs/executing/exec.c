/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ematon <ematon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:27:10 by adcisse           #+#    #+#             */
/*   Updated: 2025/03/07 17:27:00 by ematon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"

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
		return (builtin_exit(cmd->args, sh)); // close fd & free
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
		return (free(path), ft_free_toodee((void **)env_arr));
	all_path = ft_split(path, ':');
	if (!all_path)
		return ;
	free(path);
	path = find_executable(cmd->args[0], all_path);
	if (!path)
		return (printf("%s: command not found\n", cmd->args[0]),
			free_sh_cmds(sh), free_path_var(path, all_path, env_arr),
			exit(127));
	execve(path, cmd->args, env_arr);
	return (perror("execve"), free_sh_cmds(sh),
			free_path_var(path, all_path, env_arr), exit(126));
}

static void	exec_child(t_cmds *cmds, t_shell *sh, int fd_in, int fd[2])
{
	t_cmd	*cmd;
	int		status;

	cmd = cmds->cmd;
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	dup2(fd_in, STDIN_FILENO);
	if (cmds->next)
		dup2(fd[1], STDOUT_FILENO);
	close_pipes(fd_in, fd);
	if (handle_redirections(cmd->redirs) != 0)
		exit(1);
	if (!cmd->args[0])
	{
		free_sh_cmds(sh);
		exit(EXIT_SUCCESS);
	}
	if (is_builtin(cmd->args[0]))
	{
		status = exec_builtin(cmd, sh);
		free_sh_cmds(sh);
		exit(status);	
	}
		exec_external(cmd, sh);
}

static int	exec_pipeline(t_cmds *cmds, t_shell *sh)
{
	int		fd[2];
	int		fd_in;
	pid_t	pid;
	int		status;

	fd[0] = -1;
	fd[1] = -1;
	fd_in = dup(STDIN_FILENO);
	while (cmds)
	{
		if (cmds->next && pipe(fd) < 0)
			return (perror("pipe"), ERROR);
		pid = fork();
		if (pid < 0)
			return (perror("fork"), ERROR);
		if (!pid)
			exec_child(cmds, sh, fd_in, fd);
		if (cmds->next)
			close_and_swap(&fd_in, fd);
		cmds = cmds->next;
	}
	close(fd_in);
	return (wait_children(pid, &status), status);
}

void	execute(t_cmds *cmds, t_shell *sh)
{
	int		status;

	setup_signals();
	g_signal = 1;
	if (pre_process_heredocs(cmds, sh) == 10)
		return ;
	if (!cmds->next && !cmds->cmd->redirs && is_builtin(cmds->cmd->args[0]))
		sh->exit_status = exec_builtin(cmds->cmd, sh);
	else if (!cmds->next && cmds->cmd->redirs
		&& is_builtin(cmds->cmd->args[0]))
		sh->exit_status = exec_redir_builtin(cmds->cmd, sh);
	else if (cmds->cmd)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		status = exec_pipeline(cmds, sh);
		sh->exit_status = WEXITSTATUS(status);
	}
	g_signal = 0;
	setup_signals();
}
