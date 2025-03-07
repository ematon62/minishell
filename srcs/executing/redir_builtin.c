/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ematon <ematon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 17:21:55 by ematon            #+#    #+#             */
/*   Updated: 2025/03/07 14:17:29 by ematon           ###   ########.fr       */
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
	int		i;
	char	*hdfile;
	char	*itoa;

	current = cmds;
	i = 0;
	while (current)
	{
		itoa = ft_itoa(i);
		if (!itoa)
			return (free_cmds(cmds), free_shell(sh),
				exit_error("malloc"), 1);
		hdfile = ft_strjoin(HEREDOC_FILE, itoa);
		if (!hdfile)
			return (free_cmds(cmds), free_shell(sh),
				free(itoa), exit_error("malloc"), 1);
		if (process_heredocs(current->cmd->redirs, sh, hdfile) == 10)
			return (10);
		free(itoa);
		free(hdfile);
		i++;
		current = current->next;
	}
	return (0);
}
