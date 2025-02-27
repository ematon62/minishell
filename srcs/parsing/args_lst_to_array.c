/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_lst_to_array.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ematon <ematon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 12:43:45 by ematon            #+#    #+#             */
/*   Updated: 2025/02/27 12:46:39 by ematon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	malloc_size(char ***args, t_token_lst *lst)
{
	int		n;

	n = 0;
	while (lst)
	{
		n++;
		lst = lst->next;
	}
	*args = malloc(sizeof(char *) * (n + 1));
	if (!args)
		return (-1);
	return (n);
}

char	**args_lst_to_array(t_token_lst *lst)
{
	char		**args;
	int			i;
	int			n;

	i = 0;
	args = NULL;
	n = malloc_size(&args, lst);
	if (n < 0)
		return (NULL);
	while (lst)
	{
		args[i] = ft_strdup(lst->token);
		if (!args[i])
			return (ft_free_toodee((void **)args), NULL);
		lst = lst->next;
		i++;
	}
	args[i] = NULL;
	return (args);
}
