/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ematon <ematon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 16:54:48 by ematon            #+#    #+#             */
/*   Updated: 2025/02/18 16:59:34 by ematon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

//Polymorphismes de la fonction de la libft ft_lst_new

t_env_lst	*lst_env_new(char *key, char *value)
{
	t_env_lst	*elem;

	elem = malloc(sizeof(t_env_lst));
	if (!elem)
		return (NULL);
	elem->next = NULL;
	elem->key = NULL;
	elem->value = NULL;
	elem->key = ft_strdup(key);
	elem->value = ft_strdup(value);
	elem->is_env = true;
	return (elem);
}

t_token_lst	*token_lst_new(t_token type, char *token)
{
	t_token_lst	*new;

	new = malloc(sizeof(t_env_lst));
	if (!new)
		return (NULL);
	new->next = NULL;
	new->type = type;
	new->token = NULL;
	if (token)
		new->token = ft_strdup(token);
	return (new);
}
t_token_lst	*token_lst_last(t_token_lst *tokens)
{
	t_token_lst	*last;

	last = tokens;
	if (last == NULL)
		return (NULL);
	while (last->next != NULL)
		last = last->next;
	return (last);
}