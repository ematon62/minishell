/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adcisse <adcisse@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-26 11:33:22 by adcisse           #+#    #+#             */
/*   Updated: 2025-02-26 11:33:22 by adcisse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

volatile	sig_atomic_t	g_signal = 0;

static void	sigint_handler(int sig)
{
	(void)sig;
	if (g_signal == 0)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else
		write(1, "\n", 1);
	g_signal = 130;
}

static void	sigquit_handler(int sig)
{
	(void)sig;
	if (g_signal == 1)
		write(2, "Quit (core dumped)\n", 19);
	g_signal = 131;
}

void	setup_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
}
