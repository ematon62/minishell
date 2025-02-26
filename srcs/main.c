/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cisse <cisse@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 19:41:58 by ematon            #+#    #+#             */
/*   Updated: 2025/02/26 01:41:46 by cisse            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"


// /*
// cc -Wall -Wextra -Werror -no-pie  -Iincludes -Ilibft -Llibft -g srcs/main.c srcs/signals.c srcs/executing/*.c srcs/executing/builtins/*.c -lft -lreadline
// */


// int	main(int argc, char **argv, char **envp)
// {
// 	char	*input;
// 	t_shell	*shell;
// 	t_cmds	*cmds;

// 	(void)argv;
// 	(void)argc;
// 	setup_signals();
// 	shell = init_shell(envp);
// 	while (1)
// 	{
// 		if (isatty(STDIN_FILENO) && isatty(STDERR_FILENO))
// 		{
// 			input = readline("$");
// 			if (!input)
// 				break ;
// 			add_history(input);
// 			cmds = parse(input, shell);
// 			if (!cmds)
// 				continue ;
// 			execute(cmds, shell);
// 			free(input);
// 		}
// 	}
// 	free_shell(shell);
// 	printf("exit\n");
// 	return (g_signal);
// }

