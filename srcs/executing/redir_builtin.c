/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cisse <cisse@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 17:21:55 by ematon            #+#    #+#             */
/*   Updated: 2025/03/07 10:45:40 by cisse            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"

int	exec_redir_builtin(t_cmd *cmd, t_shell *sh)
{
	int	std_copy[2];
	int	status;

	save_stdio(std_copy);
	if (handle_redirections(cmd->redirs) != 0)
	{
		restore_stdio(std_copy);
		return (1);
	}
	status = exec_builtin(cmd, sh);
	restore_stdio(std_copy);
	return (status);
}

int	pre_process_heredocs(t_cmds *cmds, t_shell *sh)
{
	t_cmds	*current;

	current = cmds;
	while (current)
	{
		g_signal = 0;
		if (process_heredocs(current->cmd->redirs, sh) == 10)
			return (10);
		current = current->next;
		g_signal = 1;
	}
	return (0);
}

int	process_heredocs(t_redirections *r, t_shell *sh)
{
	char	*heredoc_file;

	while (r)
	{
		if (r->type == IS_HEREDOC)
		{
			heredoc_file = ft_strjoin(HEREDOC_FILE, ft_itoa(sh->heredoc_counter));
			printf("%s\n", heredoc_file);
			if (!heredoc_file)
				return (10); 
			if (handle_heredoc(r->target, sh, heredoc_file) == 10)
				return (free(heredoc_file), 10);
			free(r->target);
			r->target = ft_strdup(heredoc_file);
			if (!r->target)
				return (free(heredoc_file), 10); 
			r->type = IS_INREDIR;
			free(heredoc_file),
			sh->heredoc_counter++;
		}
		r = r->next;
	}
	return (0);
}

void	cleanup_heredoc_files(t_cmds *cmds)
{
	t_cmds *current_cmd;
	t_redirections *current_redir;

	current_cmd = cmds;
	while (current_cmd)
	{
		current_redir = current_cmd->cmd->redirs;
		while (current_redir)
		{
			if (current_redir->type == IS_INREDIR)
				unlink(current_redir->target);
			current_redir = current_redir->next;
		}
		current_cmd = current_cmd->next;
	}
}
