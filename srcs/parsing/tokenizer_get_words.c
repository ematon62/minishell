/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_get_words.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ematon <ematon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 19:03:25 by ematon            #+#    #+#             */
/*   Updated: 2025/03/13 08:48:07 by ematon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static char	*separate_next(char *str, int *i)
{
	char	*substr;
	int		len;
	bool	in_single;
	bool	in_double;

	in_single = false;
	in_double = false;
	while (str[*i] && (str[*i] == ' ' || str[*i] == '\t' || str[*i] == '\r'))
		*i += 1;
	len = *i;
	while (str[len])
	{
		if (!in_single && str[len] == '\"')
			in_double = !in_double;
		if (!in_double && str[len] == '\'')
			in_single = !in_single;
		if (!in_double && !in_single && str[len] == ' ')
			break ;
		len++;
	}
	substr = ft_substr(str, *i, len - *i);
	return (*i = len, substr);
}

/*
- input: sortie de la fonction readline() du main
- Les nodes contiennent les sous-chaines contenues dans l'input
separess par des espaces non-quotes
La tokenization n'est pas encore commencee, le type de token
est initialise a UNDEFINED.
*/
t_token_lst	*remove_spaces(char *input)
{
	t_token_lst	*first;
	t_token_lst	*new;
	char		*substr;
	int			i;

	i = 0;
	first = NULL;
	while (input[i])
	{
		substr = separate_next(input, &i);
		if (!substr)
			return (free_tokens_lst(first), NULL);
		if (!substr[0])
			return (free(substr), first);
		new = token_lst_new(UNDEFINED, substr);
		if (!new || (new->type == WORD && !new->token))
			return (free(substr), free_tokens_lst(first), NULL);
		ft_lstadd_back((t_list **)&first, (t_list *)new);
		free(substr);
	}
	return (first);
}
