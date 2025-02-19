/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adcisse <adcisse@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-18 15:32:25 by adcisse           #+#    #+#             */
/*   Updated: 2025-02-18 15:32:25 by adcisse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/executing.h"

int	is_numeric(char *str)
{
	size_t	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	builtin_exit(char **args, t_shell *sh)
{
	int	exit_code;

	exit_code = sh->exit_status;
	ft_putstr_fd("exit\n", STDERR_FILENO);
	if (args[1])
	{
		if (!is_numeric(args[1]))
		{
			ft_putstr_fd("exit: numeric argument required\n", STDERR_FILENO);
			exit_code = 2;
		}
		else if (args[2])
			return (ft_putstr_fd("exit: too many arguments\n", 2), 1);
		else
			exit_code = ft_atoi(args[1]);
	}
	free_shell(sh);
	// close fd
	exit(exit_code);
}
