/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ematon <ematon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:32:25 by adcisse           #+#    #+#             */
/*   Updated: 2025/03/10 12:07:02 by ematon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"


static bool	check_overflow(char *str, int *n, int index)
{
	if (*n * 10 + str[index] - 48 < *n)
		return (false);
	*n *= 10;
	*n += str[index] - 48;
	return (true);
}

static bool	is_integer(char *str)
{
	int	i;
	int	sign;
	int	n;

	i = 0;
	n = 0;
	sign = 1;
	while (str[i])
	{
		if (!i && (str[i] == '-' || str[i] == '+'))
		{
			if (str[0] == '-')
				sign *= -1;
			if (!ft_isdigit(str[i + 1]))
				return (false);
		}
		else if (!ft_isdigit(str[i]))
			return (false);
		else
			if (!check_overflow(str, &n, i))
				return (false);
		i++;
	}
	n *= sign;
	return (true);
}

int	builtin_exit(char **args, t_shell *sh)
{
	int		exit_code;
	bool	check;

	exit_code = sh->exit_status;
	check = false;
	if (args[1])
	{
		if (!is_integer(args[1]))
		{
			ft_putstr_fd("exit: numeric argument required\n", STDERR_FILENO);
			exit_code = 2;
			check = true;
		}
		else
			exit_code = ft_atoi(args[1]) % 256;
		if (!check && args[2])
			return (ft_putstr_fd("exit: too many arguments\n", STDERR_FILENO),
				1);
	}
	ft_putstr_fd("exit\n", STDERR_FILENO);
	free_cmds(sh->cmds);
	free_shell(sh);
	exit(exit_code);
}
