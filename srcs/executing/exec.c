/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ematon <ematon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:27:10 by adcisse           #+#    #+#             */
/*   Updated: 2025/03/10 14:01:40 by ematon           ###   ########.fr       */
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
		return (builtin_exit(cmd->args, sh));
	return (0);
}

void	exec_external(t_cmd *cmd, t_shell *sh)
{
	char	*path;
	char	**all_path;
	char	**env_arr;
	int		check;

	path = get_env_value(sh->env, "PATH");
	env_arr = env_to_array(sh->env);
	if (!path ||!env_arr)
		return (free(path), ft_free_toodee((void **)env_arr));
	all_path = ft_split(path, ':');
	if (!all_path)
		return ;
	free(path);
	path = find_executable(cmd->args[0], all_path);
	check = check_invalid_path(path, cmd, sh);
	if (check)
	{
		free_path_var(path, all_path, env_arr);
		exit(check);
	}
	execve(path, cmd->args, env_arr);
	return (free_sh_cmds(sh), free_path_var(path, all_path, env_arr), exit(126));
}

static void	exec_child(t_cmds *cmds, t_shell *sh, int fd_in, int fd[2])
{
	t_cmd	*cmd;
	int		status;

	cmd = cmds->cmd;
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
	signal(SIGINT, child_sigint);
	signal(SIGQUIT, child_sigquit);
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
	return (wait_children(pid, &status, sh));
}

void	execute(t_cmds *cmds, t_shell *sh)
{
	int		std_copy[2];

	setup_signals();
	save_stdio(std_copy);
	g_signal = 1;
	if (pre_process_heredocs(cmds, sh) == 10)
		return (restore_stdio(std_copy));
	if (!cmds->next && !cmds->cmd->redirs
		&& is_builtin(cmds->cmd->args[0]))
	{
		restore_stdio(std_copy);
		sh->exit_status = exec_builtin(cmds->cmd, sh);
	}
	else if (!cmds->next && cmds->cmd->redirs
		&& is_builtin(cmds->cmd->args[0]))
		sh->exit_status = exec_redir_builtin(cmds->cmd, sh);
	else if (cmds->cmd)
	{
		restore_stdio(std_copy);
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		exec_pipeline(cmds, sh);
	}
	cleanup_heredoc_files(cmds);
	setup_signals();
}
