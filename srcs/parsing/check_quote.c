/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ematon <ematon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 18:52:29 by ematon            #+#    #+#             */
/*   Updated: 2025/02/17 13:08:06 by ematon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	change_quote_status(bool *quote)
{
	if (*quote)
		*quote = false;
	else
		*quote = true;
}

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
			change_quote_status(&is_double);
		if (!is_double && input[i] == '\'')
			change_quote_status(&is_single);
		i++;
	}
	return (is_single || is_double);
}
