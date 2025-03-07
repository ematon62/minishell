/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ematon <ematon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 13:34:35 by adcisse           #+#    #+#             */
/*   Updated: 2025/03/07 18:10:36 by ematon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"

static bool	check_n(char *str)
{
	int		i;

	i = 1;
	while (str[i])
	{
		if (str[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

static bool	is_option(char *str, bool *newline, int *i)
{
	if (str && str[0] == '-' && str[1])
	{
		if (check_n(str))
		{
			*newline = false;
			*i += 1;
			return (true);
		}
	}
	return (false);
}

int	builtin_echo(char **args)
{
	int		i;
	bool	newline;
	bool	is_words;

	i = 1;
	newline = true;
	is_words = false;
	while (args[i])
	{
		if (!is_words && is_option(args[i], &newline, &i))
			continue ;
		is_words = true;
		ft_putstr_fd(args[i], STDOUT_FILENO);
		if (args[++i])
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
	if (newline)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}
