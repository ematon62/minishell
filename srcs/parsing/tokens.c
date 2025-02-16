/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ematon <ematon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 19:03:25 by ematon            #+#    #+#             */
/*   Updated: 2025/02/16 18:55:52 by ematon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static t_token	get_redir_type(char *str, int *i)
{
	if (str[*i] == '|')
		return (*i += 1, IO_PIPE);
	else if (str[*i] == '<')
	{
		if (str[*i + 1] == '<')
			return (*i += 2, IO_HEREDOC);
		return (*i += 1, IO_IN);
	}
	else if (str[*i] == '>')
	{
		if (str[*i + 1] == '>')
			return (*i += 2, IO_APPEND);
		return (*i += 1, IO_OUT);
	}
	else
		return (WORD);
}

static void	add_tokens(t_token_lst *tokens, char *str)
{
	t_token_lst	*new;
	t_token		type;
	int			i;

	i = 0;
	new = NULL;
	while (str[i])
	{
		if (ft_strchr("|<>", str[i]))
			type = get_redir_type(str, &i);
		else
		{
			type = WORD;
			while (str[i] && !ft_strchr("|<>", str[i]))
				i++;
		}
		new = token_lst_new(type);
		if (!new)
			exit_error("malloc");
		ft_lstadd_back((t_list **)&tokens, (t_list *)new);
	}
}

t_token_lst	*tokenize(char *input)
{
	t_token_lst	*tokens;
	char		**split;
	int			i;

	tokens = NULL;
	split = ft_split(input, ' ');
	if (!split)
		return (exit_error("malloc"), NULL);
	i = 0;
	while (split[i])
	{
		add_tokens(tokens, split[i]);
		i++;
	}
	return (tokens);
}

int main()
{
	// while (caca)
	// {
	// 	if (caca->type == WORD)
	// 		printf("WORD\n");
	// 	else if (caca->type == IO_PIPE)
	// 		printf("IO_PIPE\n");
	// 	else if (caca->type == IO_APPEND)
	// 		printf("IO_APPEND\n");
	// 	else if (caca->type == IO_IN)
	// 		printf("IO_IN\n");
	// 	else if (caca->type == IO_OUT)
	// 		printf("IO_OUT\n");
	// 	else if (caca->type == IO_HEREDOC)
	// 		printf("IO_HEREDOC\n");
	// 	caca = caca->next;
	// }

}