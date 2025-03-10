/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ematon <ematon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 17:21:55 by ematon            #+#    #+#             */
/*   Updated: 2025/03/10 17:13:13 by ematon           ###   ########.fr       */
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

void	cleanup_heredoc_files(t_cmds *cmds)
{
	t_cmds			*current_cmd;
	t_redirections	*current_redir;

	current_cmd = cmds;
	while (current_cmd)
	{
		current_redir = current_cmd->cmd->redirs;
		while (current_redir)
		{
			if (current_redir->type == IS_HEREDOC)
				unlink(current_redir->target);
			current_redir = current_redir->next;
		}
		current_cmd = current_cmd->next;
	}
}
