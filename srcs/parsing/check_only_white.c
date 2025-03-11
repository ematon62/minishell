/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_only_white.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ematon <ematon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:21:21 by ematon            #+#    #+#             */
/*   Updated: 2025/03/11 16:35:25 by ematon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/*
Check si après expansion, il n'y a que du vide
*/
bool	check_only_white(t_token_lst *tokens)
{
	t_token_lst	*current;

	current = tokens;
	while (current)
	{
		if (current->type == WORD && current->token
			&& !is_whitespace(current->token))
			return (false);
		current = current->next;
	}
	return (true);
}
