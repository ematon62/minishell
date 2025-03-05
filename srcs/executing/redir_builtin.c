





#include "../../includes/executing.h"

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
	t_cmds *current = cmds;
	while (current)
	{
		if(process_heredocs(current->cmd->redirs, sh) == 10)
				return (10);
		current = current->next;
	}
	return (0);
}
