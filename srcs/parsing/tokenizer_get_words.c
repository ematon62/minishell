/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_get_words.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ematon <ematon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 19:03:25 by ematon            #+#    #+#             */
/*   Updated: 2025/02/18 14:09:41 by ematon           ###   ########.fr       */
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
	while (str[*i] && str[*i] == ' ')
		*i += 1;
	len = *i;
	while (str[len])
	{
		if (!in_single && str[len] == '\"')
			change_quote_status(&in_double);
		if (!in_double && str[len] == '\'')
			change_quote_status(&in_single);
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
t_token_lst	*remove_spaces(char *input, t_shell *shell)
{
	t_token_lst	*first;
	t_token_lst	*new;
	char		*substr;
	int			i;

	(void)shell;
	i = 0;
	first = NULL;
	while (input[i])
	{
		substr = separate_next(input, &i);
		if (!substr)
			return (free_tokens_lst(first), free_shell(shell),
				free(input), exit_error("malloc"), NULL);
		if (!substr[0])
			return (free(substr), first);
		new = token_lst_new(UNDEFINED, substr);
		if (!new || (new->type == WORD && !new->token))
			return (free(substr), free_tokens_lst(first),
				free_shell(shell), free_tokens_lst(new),
				free(input), exit_error("malloc"), NULL);
		ft_lstadd_back((t_list **)&first, (t_list *)new);
		free(substr);
	}
	return (first);
}
