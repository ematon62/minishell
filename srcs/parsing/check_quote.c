/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ematon <ematon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 18:52:29 by ematon            #+#    #+#             */
/*   Updated: 2025/02/27 13:04:04 by ematon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/*
input: sortie de la fonction readline()
Check si input contient des quotes non fermées
*/
bool	is_unclosed_quote(char *input)
{
	bool	is_single;
	bool	is_double;
	int		i;

	i = 0;
	is_single = false;
	is_double = false;
	while (input[i])
	{
		if (!is_single && input[i] == '\"')
			is_double = !is_double;
		if (!is_double && input[i] == '\'')
			is_single = !is_single;
		i++;
	}
	return (is_single || is_double);
}
