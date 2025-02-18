/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ematon <ematon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 18:59:46 by ematon            #+#    #+#             */
/*   Updated: 2025/02/18 18:20:49 by ematon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_cmds	*parse(char *input, t_shell *shell)
{
	// t_cmds		*cmds;
	t_token_lst	*tokens;

	if (is_unclosed_quote(input))
		return (ft_putstr_fd(MATCHING_QUOTE, STDERR_FILENO), NULL);
	tokens = lexer(input, shell);
	if (!complete_pipe(tokens, shell))
		return (free_tokens_lst(tokens), NULL);
	return (NULL);
}
