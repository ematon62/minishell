/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ematon <ematon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 19:41:58 by ematon            #+#    #+#             */
/*   Updated: 2025/02/11 15:37:21 by ematon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern struct sigaction	sigac;

void	catch_signal(int signal)
{
	if (signal == SIGINT)
		ft_printf("youpi\n");
	if (signal == SIGQUIT)
		ft_printf("youpooo\n");
}

int	main(void)
{
	char 	*input;
	char	**split;
	int		i;

	while (1)
	{
		input = readline("$");
		add_history(input);
		split = ft_split(input, ' ');
		i = 0;
		while(split[i])
		{
			ft_printf("%s\n", split[i]);
			i++;
		}
		if (!input || !input[0])
		{
			free(input);
			break ;
		}
		free(input);
	}
}
