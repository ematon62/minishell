/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adcisse <adcisse@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-18 15:33:32 by adcisse           #+#    #+#             */
/*   Updated: 2025-02-18 15:33:32 by adcisse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/executing.h"

int	builtin_pwd(void)
{
	char	cwd[PATH_MAX];

	if (!getcwd(cwd, PATH_MAX))
		return (perror("pwd"), 1);
	ft_putendl_fd(cwd, STDOUT_FILENO);
	return (0);
}
