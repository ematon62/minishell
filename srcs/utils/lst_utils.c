/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ematon <ematon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 16:54:48 by ematon            #+#    #+#             */
/*   Updated: 2025/02/17 11:34:31 by ematon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

//Polymorphismes de la fonction de la libft ft_lst_new

t_env_lst	*lst_env_new(char *key, char *value)
{
	t_env_lst	*elem;

	elem = malloc(sizeof(t_env_lst));
	if (!elem)
		exit_error("malloc");
	elem->next = NULL;
	elem->key = NULL;
	elem->value = NULL;
	elem->key = ft_strdup(key);
	if (!elem->key)
		exit_error("malloc");
	elem->value = ft_strdup(value);
	if (!elem->value)
		exit_error("malloc");
	elem->is_env = true;
	return (elem);
}

t_token_lst	*token_lst_new(t_token type, char *token)
{
	t_token_lst	*new;

	new = malloc(sizeof(t_env_lst));
	if (!new)
		exit_error("malloc");
	new->token = ft_strdup(token);
	if (!new->token)
		exit_error("malloc");
	new->type = type;
	new->next = NULL;
	return (new);
}