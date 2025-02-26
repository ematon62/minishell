/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ematon <ematon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 18:59:46 by ematon            #+#    #+#             */
/*   Updated: 2025/02/26 14:41:58 by ematon           ###   ########.fr       */
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

void	quoteless(char *token)
{
	int		j;
	int		i;
	bool	in_single;
	bool	in_double;

	i = 0;
	j = 0;
	in_single = false;
	in_double = false;
	while (token[i])
	{
		if (!in_single && token[i] == '\"')
			in_double = !in_double;
		else if (!in_double && token[i] == '\'')
			in_single = !in_single;
		else if ((in_single && token[i] != '\'')
			|| (in_double && token[i] != '\"')
			|| (!in_double && !in_single))
		{
			token[j] = token[i];
			j++;
		}
		i++;
	}
	token[j] = 0;
}

void	remove_quotes(t_token_lst *tokens)
{
	while (tokens)
	{
		if (tokens->type == WORD)
			quoteless(tokens->token);
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
	remove_quotes(tokens);
	return (NULL);
}
