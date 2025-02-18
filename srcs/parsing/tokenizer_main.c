/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ematon <ematon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 19:03:25 by ematon            #+#    #+#             */
/*   Updated: 2025/02/18 14:11:33 by ematon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static t_token_lst	*get_word(char *word, int *i, bool s, bool d)
{
	char		*substr;
	int			len;
	t_token_lst	*new;

	len = *i;
	while (word[len])
	{
		if (ft_strchr("|<>", word[len]) && !s && !d)
			break ;
		if (!s && word[*i] == '\"')
			change_quote_status(&d);
		if (!d && word[*i] == '\'')
			change_quote_status(&s);
		len++;
	}
	substr = ft_substr(word, *i, len - *i);
	if (!substr)
		return (NULL);
	new = token_lst_new(WORD, substr);
	*i = len;
	return (free(substr), new);
}

static t_token_lst	*get_next_token(char *word, int *i)
{
	bool	in_single;
	bool	in_double;

	in_single = false;
	in_double = false;
	if (!in_single && word[*i] == '\"')
		change_quote_status(&in_double);
	if (!in_double && word[*i] == '\'')
		change_quote_status(&in_single);
	if (!in_single && !in_double && word[*i] == '|')
		return (*i += 1, token_lst_new(IO_PIPE, NULL));
	else if (!in_single && !in_double && word[*i] == '<')
	{
		if (word[*i + 1] == '<')
			return (*i += 2, token_lst_new(IO_HEREDOC, NULL));
		return (*i += 1, token_lst_new(IO_IN, NULL));
	}
	else if (!in_single && !in_double && word[*i] == '>')
	{
		if (word[*i + 1] == '>')
			return (*i += 2, token_lst_new(IO_APPEND, NULL));
		return (*i += 1, token_lst_new(IO_OUT, NULL));
	}
	else
		return (get_word(word, i, in_single, in_double));
}

static t_token_lst	*tokenize_node(t_token_lst *current, t_shell *shell)
{
	int			i;
	t_token_lst	*new_lst;
	t_token_lst	*new_node;

	i = 0;
	new_lst = NULL;
	while (current->token[i])
	{
		new_node = get_next_token(current->token, &i);
		if (!new_node || (new_node->type == WORD && !new_node->token))
			return (free_tokens_lst(new_node),
				free_tokens_lst(new_lst),
				free_shell(shell),
				exit_error("malloc"), NULL);
		ft_lstadd_back((t_list **)&new_lst, (t_list *)new_node);
	}
	return (new_lst);
}

static t_token_lst	*words_to_tokens(t_token_lst *first, t_shell *shell)
{
	t_token_lst	*current;
	t_token_lst	*tokens;
	t_token_lst	*new;

	tokens = NULL;
	current = first;
	while (current)
	{
		new = tokenize_node(current, shell);
		ft_lstadd_back((t_list **)&tokens, (t_list *)new);
		current = current->next;
	}
	return (tokens);
}

/*
- input: sortie de readline()
- Tokenize la chaine (->liste chainee)
Ex: cat > outfile | echo << EOF
->1ere node: cat WORD
->2e: > OUT_REDIRECTION
->3e: outfile WORD
->4e: | PIPE
->5e: echo WORD
->6e: << HERE_DOC
->7e: EOF WORD
*/
t_token_lst	*lexer(char *input, t_shell *shell)
{
	t_token_lst	*new;
	t_token_lst	*first;

	first = remove_spaces(input, shell);
	free(input);
	new = words_to_tokens(first, shell);
	free_tokens_lst(first);
	return (new);
}
