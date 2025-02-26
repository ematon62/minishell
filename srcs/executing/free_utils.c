/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adcisse <adcisse@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-26 11:20:13 by adcisse           #+#    #+#             */
/*   Updated: 2025-02-26 11:20:13 by adcisse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executing.h"

void	free_utils(char *path, char **all_path, char **env_arr)
{
	free(path);
	free_array(all_path);
	free_array(env_arr);
}
