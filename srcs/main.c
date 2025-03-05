/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cisse <cisse@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 19:41:58 by ematon            #+#    #+#             */
/*   Updated: 2025/03/05 15:37:18 by cisse            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cisse <cisse@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 19:41:58 by ematon            #+#    #+#             */
/*   Updated: 2025/03/02 21:22:51 by cisse            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"
#include "minishell.h"
#include "structs.h"
#include "utils.h"
#include "parsing.h"


int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_shell	*shell;

	(void)argv;
	(void)argc;
	setup_signals();
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
			add_history(input);
			if (!input[0])
				continue ;
			shell->cmds = parse(input, shell);
			if (!shell->cmds)
				continue ;
			execute(shell->cmds, shell);
			free_cmds(shell->cmds);
		}
	}
	free_shell(shell);
	return (0);
}

