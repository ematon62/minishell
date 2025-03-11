/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ematon <ematon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 18:59:46 by ematon            #+#    #+#             */
/*   Updated: 2025/03/11 16:56:09 by ematon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	*expand_dollars(t_token_lst *tokens, t_shell *shell)
{
	if (tokens && tokens->type == WORD)
	{
		tokens->token = expand_var(tokens->token, shell);
		if (!tokens->token)
			return (NULL);
	}
	while (tokens)
	{
		if (tokens->type != IO_HEREDOC && tokens->next
			&& tokens->next->type == WORD)
		{
			tokens->next->token = expand_var(tokens->next->token, shell);
			if (!tokens->next->token)
				return (NULL);
		}
		tokens = tokens->next;
	}
	return ((void *)1);
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

bool	is_whitespace(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] != ' ' && input[i] != '\t' && input[i] != '\n')
			return (false);
		i++;
	}
	return (true);
}

/*
input est free au passage
*/
t_cmds	*parse(char *input, t_shell *shell)
{
	t_token_lst	*tokens;
	t_cmds		*cmds;

	if (is_unclosed_quote(input))
		return (free(input), ft_putstr_fd(MATCHING, STDERR_FILENO),
			shell->exit_status = 2, NULL);
	if (is_whitespace(input))
		return (free(input), NULL);
	tokens = lexer(input);
	if (!tokens)
		return (free_shell(shell), exit_error("malloc"), NULL);
	if (!check_tokens(tokens))
		return (free_tokens_lst(tokens), shell->exit_status = 2,
			NULL);
	expand_dollars(tokens, shell);
	if (check_only_white(tokens))
		return (free_tokens_lst(tokens), NULL);
	remove_quotes(tokens);
	cmds = tokens_to_cmds(tokens);
	free_tokens_lst(tokens);
	if (!cmds)
		return (free_shell(shell), exit_error("malloc"), NULL);
	return (cmds);
}
