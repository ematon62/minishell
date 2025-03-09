/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ematon <ematon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 11:33:22 by adcisse           #+#    #+#             */
/*   Updated: 2025/03/09 19:00:44 by ematon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signal = 0;

void	heredoc_sigint(int sig)
{
	(void)sig;
	g_signal = 130;
	printf("\n");
	close(STDIN_FILENO);
}

void	child_sigint(int sig)
{
	(void)sig;
	g_signal = 130;
	printf("\n");
}

void	child_sigquit(int sig)
{
	(void)sig;
	g_signal = 131;
	ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
}

void	sigint_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_signal = 130;
}

void	setup_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}
