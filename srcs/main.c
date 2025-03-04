/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ematon <ematon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 19:41:58 by ematon            #+#    #+#             */
/*   Updated: 2025/03/04 16:46:11 by ematon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_signal;

void	test(t_cmds *cmds)
{
	int	i;
	t_redirections	*temp;

	while (cmds)
	{
		i = 0;
		printf("WORDS\n");
		while (cmds->cmd->args[i])
		{
			printf("%s ", cmds->cmd->args[i]);
			i++;
		}
		printf("\nREDIRS\n");
		temp = cmds->cmd->redirs;
		while (cmds->cmd->redirs)
		{
			printf("%d %s\n", cmds->cmd->redirs->type, cmds->cmd->redirs->target);
			cmds->cmd->redirs = cmds->cmd->redirs->next;
		}
		cmds->cmd->redirs = temp;
		printf("\n");
		cmds = cmds->next;
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_shell	*shell;

	(void)argv;
	(void)argc;
	shell = init_shell(envp); 
	if (!shell)
		exit_error("malloc");
	while (1)
	{
		if (isatty(STDIN_FILENO) && isatty(STDERR_FILENO))
		{
			input = readline("$");
			if (!input)
				break ;
			shell->cmds = parse(input, shell);
			if (!shell->cmds)
				continue ;
			test(shell->cmds);
			free_cmds(shell->cmds);
		}
	}
	free_shell(shell);
	printf("exit\n");
	return (0);
}
