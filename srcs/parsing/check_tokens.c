/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ematon <ematon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:29:55 by ematon            #+#    #+#             */
/*   Updated: 2025/03/06 14:17:15 by ematon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	check_tokens(t_token_lst *tokens)
{
	if (tokens && tokens->type == IO_PIPE)
		return (ft_putstr_fd(SYNTAX, STDERR_FILENO), false);
	while (tokens)
	{
		if ((tokens->type >= 1 && tokens->type <= 4)
			&& !tokens->next)
			return (ft_putstr_fd(SYNTAX, STDERR_FILENO), false);
		if ((tokens->type >= 1 && tokens->type <= 4) && tokens->next
			&& tokens->next->type != WORD)
			return (ft_putstr_fd(SYNTAX, STDERR_FILENO), false);
		if (tokens->type == IO_PIPE && !tokens->next)
			return (ft_putstr_fd(SYNTAX, STDERR_FILENO), false);
		tokens = tokens->next;
	}
	return (true);
}
