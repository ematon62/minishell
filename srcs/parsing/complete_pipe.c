/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complete_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ematon <ematon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:21:21 by ematon            #+#    #+#             */
/*   Updated: 2025/02/26 13:33:08 by ematon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/*
- tokens: liste de tokens après 1er appel du lexer
- Si dernier token est une pipe, fonction est appelée
pour complèter cette pipe (en vérifiant tokens au passage)
*/
bool	complete_pipe(t_token_lst *tokens, t_shell *shell)
{
	char		*read_line;
	t_token_lst	*added_tokens;

	if (!check_tokens(tokens))
		return (false);
	while (tokens && token_lst_last(tokens)->type == IO_PIPE)
	{
		read_line = readline(">");
		added_tokens = lexer(read_line, shell);
		ft_lstadd_back((t_list **)tokens, (t_list *)added_tokens);
		if (!check_tokens(tokens))
			return (false);
	}
	return (true);
}
