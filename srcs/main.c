/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ematon <ematon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 19:41:58 by ematon            #+#    #+#             */
/*   Updated: 2025/02/14 13:27:27 by ematon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern struct sigaction	sigac;

int	main(char **envp)
{
	char 	*input;
	t_shell	*shell;
	t_cmds	*cmds;

	while (1)
	{
		input = readline("$");
		add_history(input);
		shell = init_shell(envp);
	}
}
