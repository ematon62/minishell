/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ematon <ematon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 19:03:25 by ematon            #+#    #+#             */
/*   Updated: 2025/02/17 14:39:59 by ematon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*get_next_word(char *str, int *i)
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
- Renvoie une liste chainee t_token_lst
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
		substr = get_next_word(input, &i);
		if (!substr)
			exit_error("malloc");
		if (!substr[0])
		{
			free(substr);
			break ;
		}
		new = token_lst_new(UNDEFINED, substr);
		if (!new)
			exit_error("malloc");
		ft_lstadd_back((t_list ** )&first, (t_list *)new); 
		free(substr);
	}
	return (first);
}

t_token_lst	*get_next_token(char *word, int *i)
{
	char	*substr;
	int		len;
}

t_token_lst	*tokenize(t_token_lst *current)
{
	int			i;
	int			len;
	char		*current_token;
	t_token		current_type;
	t_token_lst	*new;

	i = 0;
	new = NULL;
	while (current_token[i])
	{
		
	}
}

t_token_lst	*lexer(t_token_lst *first)
{
	t_token_lst	*current;
	
	t_token_lst	*tokens;

	tokens = NULL;
	current = first;
	while (current)
	{
		
	}
}