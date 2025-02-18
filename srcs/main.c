/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cisse <cisse@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 19:41:58 by ematon            #+#    #+#             */
/*   Updated: 2025/02/17 00:28:02 by cisse            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"

extern int	g_exit_signal;

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_shell	*shell;
	t_cmds	*cmds;

	(void)argv;
	(void)argc;
	shell = init_shell(envp);
	while (1)
	{
		if (isatty(STDIN_FILENO) && isatty(STDERR_FILENO))
		{
			input = readline("$");
			if (!input)
				break ;
			add_history(input);
			cmds = parse(input, shell);
			if (!cmds)
				continue ;
			execute(cmds, shell);
			free(input);
		}
	}
	free_shell(shell);
	printf("exit\n");
	return (0);
}
