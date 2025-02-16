/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ematon <ematon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 18:59:46 by ematon            #+#    #+#             */
/*   Updated: 2025/02/16 16:29:22 by ematon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_cmds	*parse(char *input)
{
	if (is_unclosed_quote(input))
		return (ft_putstr_fd(MATCHING_ERR, STDERR_FILENO), NULL);
	return ((t_cmds *)1);
}
