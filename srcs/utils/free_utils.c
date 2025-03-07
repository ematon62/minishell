/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ematon <ematon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 11:20:13 by adcisse           #+#    #+#             */
/*   Updated: 2025/03/07 15:41:35 by ematon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"

void	free_path_var(char *path, char **all_path, char **env_arr)
{
	free(path);
	ft_free_toodee((void **)all_path);
	ft_free_toodee((void **)env_arr);
}

void	free_sh_cmds(t_shell *shell)
{
	free_cmds(shell->cmds);
	free_shell(shell);
}
