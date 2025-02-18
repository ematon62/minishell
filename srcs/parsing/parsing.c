/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ematon <ematon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 18:59:46 by ematon            #+#    #+#             */
/*   Updated: 2025/02/18 20:31:36 by ematon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	expand_dollars(t_token_lst *tokens, t_shell *shell)
{
	if (tokens && tokens->type == WORD)
		tokens->token = expand_var(tokens->token, shell);
	while (tokens)
	{
		if (tokens->type != IO_HEREDOC && tokens->next
			&& tokens->next->type == WORD)
			tokens->next->token = expand_var(tokens->next->token, shell);
		tokens = tokens->next;
	}
}

t_cmds	*parse(char *input, t_shell *shell)
{
	t_token_lst	*tokens;

	if (is_unclosed_quote(input))
		return (ft_putstr_fd(MATCHING, STDERR_FILENO), NULL);
	tokens = lexer(input, shell);
	if (!complete_pipe(tokens, shell))
		return (free_tokens_lst(tokens), NULL);
	expand_dollars(tokens, shell);
	while (tokens)
	{
		printf("%s\n", tokens->token);
		tokens = tokens->next;
	}
	// return (tokens_to_cmds(tokens, shell));
	return (NULL);
}
