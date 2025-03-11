/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ematon <ematon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 19:41:58 by ematon            #+#    #+#             */
/*   Updated: 2025/03/10 18:17:40 by ematon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_shell	*shell;

	shell = init_shell(envp, argc, argv);
	while (1 && isatty(STDIN_FILENO) && isatty(STDERR_FILENO))
	{
		setup_signals();
		input = readline("$");
		if (!input)
			break ;
		if (!input[0])
			continue ;
		add_history(input);
		shell->cmds = parse(input, shell);
		if (!shell->cmds)
			continue ;
		execute(shell->cmds, shell);
		free_cmds(shell->cmds);
	}
	printf("exit\n");
	free_shell(shell);
	return (0);
}
