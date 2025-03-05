/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ematon <ematon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 16:54:48 by ematon            #+#    #+#             */
/*   Updated: 2025/03/05 15:14:26 by ematon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

//Polymorphismes de la fonction de la libft ft_lst_new

/*
key et value sont déja allouées dynamiquement
*/
t_env_lst	*lst_env_new(char *key, char *value)
{
	t_env_lst	*elem;

	elem = malloc(sizeof(t_env_lst));
	if (!elem)
		return (free(key), free(value), NULL);
	elem->next = NULL;
	elem->key = key;
	elem->value = value;
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
	{
		new->token = ft_strdup(token);
		if (!new->token)
			return (free(new), NULL);
	}
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

t_redirections	*lst_redir_new(t_token token_type, char *target)
{
	t_redirections	*redir;

	redir = malloc(sizeof(t_redirections));
	if (!redir)
		return (NULL);
	if (token_type == IO_IN)
		redir->type = IS_INREDIR;
	if (token_type == IO_OUT)
		redir->type = IS_TRUNCAT;
	if (token_type == IO_HEREDOC)
		redir->type = IS_HEREDOC;
	if (token_type == IO_APPEND)
		redir->type = IS_APPEND;
	redir->target = ft_strdup(target);
	if (!redir->target)
		return (free(redir), NULL);
	redir->next = NULL;
	return (redir);
}

t_cmds	*lst_new_cmds(t_cmd *cmd)
{
	t_cmds	*cmds;

	cmds = malloc(sizeof(t_cmds));
	if (!cmds)
		return (NULL);
	cmds->next = NULL;
	cmds->cmd = cmd;
	return (cmds);
}
