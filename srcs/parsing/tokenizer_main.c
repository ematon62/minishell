/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ematon <ematon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 19:03:25 by ematon            #+#    #+#             */
/*   Updated: 2025/03/04 18:27:03 by ematon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static t_token_lst	*get_word(char *word, int *i, bool *s, bool *d)
{
	char		*substr;
	int			len;
	t_token_lst	*new;

	len = *i;
	while (word[len])
	{
		if (ft_strchr("|<>", word[len]) && !*s && !*d)
			break ;
		if (!*s && word[len] == '\"')
			*d = !*d;
		if (!*d && word[len] == '\'')
			*s = !*s;
		len++;
	}
	substr = ft_substr(word, *i, len - *i);
	if (!substr)
		return (NULL);
	new = token_lst_new(WORD, substr);
	*i = len;
	return (free(substr), new);
}

static t_token_lst	*get_next_token(char *word, int *i, bool *in_single,
	bool *in_double)
{
	if (!*in_single && word[*i] == '\"')
	{
		*in_double = !*in_double;
		*i += 1;
	}
	if (!*in_double && word[*i] == '\'')
	{
		*in_single = !*in_single;
		*i += 1;
	}
	if (!*in_single && !*in_double && word[*i] == '|')
		return (*i += 1, token_lst_new(IO_PIPE, NULL));
	else if (!*in_single && !*in_double && word[*i] == '<')
	{
		if (word[*i + 1] == '<')
			return (*i += 2, token_lst_new(IO_HEREDOC, NULL));
		return (*i += 1, token_lst_new(IO_IN, NULL));
	}
	else if (!*in_single && !*in_double && word[*i] == '>')
	{
		if (word[*i + 1] == '>')
			return (*i += 2, token_lst_new(IO_APPEND, NULL));
		return (*i += 1, token_lst_new(IO_OUT, NULL));
	}
	return (get_word(word, i, in_single, in_double));
}

static t_token_lst	*tokenize_node(t_token_lst *current)
{
	int			i;
	t_token_lst	*new_lst;
	t_token_lst	*new_node;
	bool		in_single;
	bool		in_double;

	in_single = false;
	in_double = false;
	i = 0;
	new_lst = NULL;
	while (current->token[i])
	{
		new_node = get_next_token(current->token, &i, &in_single, &in_double);
		if (!new_node || (new_node->type == WORD && !new_node->token))
			return (free_tokens_lst(new_node),
				free_tokens_lst(new_lst), NULL);
		ft_lstadd_back((t_list **)&new_lst, (t_list *)new_node);
	}
	return (new_lst);
}

static t_token_lst	*words_to_tokens(t_token_lst *first)
{
	t_token_lst	*tokens;
	t_token_lst	*new;

	tokens = NULL;
	while (first)
	{
		new = tokenize_node(first);
		if (!new)
			return (free_tokens_lst(tokens), NULL);
		ft_lstadd_back((t_list **)&tokens, (t_list *)new);
		first = first->next;
	}
	return (tokens);
}

/*
- input: sortie de readline()
- Tokenize la chaine (->liste chainee)
!!!!Au passage, free la chaine d'entree input
*/
t_token_lst	*lexer(char *input)
{
	t_token_lst	*new;
	t_token_lst	*first;

	first = remove_spaces(input);
	if (!first)
		return (free(input), NULL);
	free(input);
	new = words_to_tokens(first);
	free_tokens_lst(first);
	return (new);
}
