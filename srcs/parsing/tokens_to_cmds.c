/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_to_cmds.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ematon <ematon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 18:28:27 by ematon            #+#    #+#             */
/*   Updated: 2025/03/04 15:11:33 by ematon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	*complete_cmd(t_token_lst *tokens, t_redirections **redirs,
	t_token_lst **args)
{
	t_redirections	*new_redir;
	t_token_lst		*new_arg;

	if (tokens->type != WORD)
	{
		new_redir = lst_redir_new(tokens->type, tokens->next->token);
		if (!new_redir)
			return (NULL);
		ft_lstadd_back((t_list **)redirs, (t_list *)new_redir);
	}
	else
	{
		new_arg = token_lst_new(WORD, tokens->token);
		if (!new_arg)
			return (NULL);
		ft_lstadd_back((t_list **)args, (t_list *)new_arg);
	}
	return ((void *)1);
}

t_token_lst	*cycle_until_pipe(t_token_lst *tokens, t_cmd *cmd)
{
	t_redirections	*redirs;
	t_token_lst		*arg_lst;

	redirs = NULL;
	arg_lst = NULL;
	while (tokens && tokens->type != IO_PIPE)
	{
		if (!complete_cmd(tokens, &redirs, &arg_lst))
			return (free(cmd), free_tokens_lst(arg_lst),
				free_redirs(redirs), NULL);
		if (tokens->type != WORD)
			tokens = tokens->next;
		if (tokens)
			tokens = tokens->next;
	}
	cmd->args = args_lst_to_array(arg_lst);
	free_tokens_lst(arg_lst);
	if (!cmd->args)
		return (free(cmd), free_tokens_lst(arg_lst),
			free_redirs(redirs), NULL);
	cmd->redirs = redirs;
	return (tokens);
}

t_cmds	*tokens_to_cmds(t_token_lst *tokens)
{
	t_cmds			*cmds;
	t_cmds			*new;
	t_cmd			*cmd;

	cmds = NULL;
	while (tokens)
	{
		cmd = malloc(sizeof(t_cmd));
		if (!cmd)
			return (free_cmds(cmds), NULL);
		tokens = cycle_until_pipe(tokens, cmd);
		new = lst_new_cmds(cmd);
		if (!new)
			return (free_cmds(cmds), ft_free_toodee((void **)cmd->args),
				free_redirs(cmd->redirs), free(cmd), NULL);
		ft_lstadd_back((t_list **)&cmds, (t_list *)new);
		if (tokens)
			tokens = tokens->next;
	}
	return (cmds);
}
