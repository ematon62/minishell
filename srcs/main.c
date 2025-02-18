/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ematon <ematon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 19:41:58 by ematon            #+#    #+#             */
/*   Updated: 2025/02/18 10:56:42 by ematon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_signal;

// int	main(int argc, char **argv, char **envp)
// {
// 	char	*input;
// 	t_shell	*shell;

// 	(void)argv;
// 	(void)argc;
// 	shell = init_shell(envp);
// 	while (1)
// 	{
// 		if (isatty(STDIN_FILENO) && isatty(STDERR_FILENO))
// 		{
// 			input = readline("$");
// 			if (!input)
// 				break ;
// 			add_history(input);
// 			shell->cmds = parse(input, shell);
// 			if (!shell->cmds)
// 			{
// 				// free_stuff
// 				continue ;
// 			}
// 		}
// 	}
// 	free_shell(shell);
// 	printf("exit\n");
// 	return (0);
// }
