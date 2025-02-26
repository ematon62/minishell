/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_to_cmds.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ematon <ematon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 18:28:27 by ematon            #+#    #+#             */
/*   Updated: 2025/02/26 15:15:56 by ematon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	malloc_size(char ***args, t_token_lst *lst,
	t_token_lst *tokens, t_shell *sh)
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

char	**args_lst_to_array(t_token_lst *lst, t_token_lst *tok, t_shell *sh)
{
	char		**args;
	int			i;
	int			n;

	i = 0;
	args = NULL;
	n = malloc_size(&args, lst, tok, sh);
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

t_cmd	*cycle_until_pipe(t_token_lst *tokens, t_shell *shell)
{
	t_cmd			*cmd;
	t_redirections	*redirs;
	t_redirections	*new_redir;
	t_token_lst		*arg_lst;
	t_token_lst		*new_arg;

	redirs = NULL;
	arg_lst = NULL;
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	while (tokens && tokens->type != IO_PIPE)
	{
		if (tokens->type != WORD)
		{
			new_redir = lst_redir_new(tokens->type, tokens->token);
			if (!new_redir)
				return (free_tokens_lst(tokens), free(cmd),
					free_shell(shell), NULL);
			ft_lstadd_back((t_list **)redirs, (t_list *)new_redir);
			tokens = tokens->next;
		}
		else
		{
			
		}
		tokens = tokens->next;
	}
	cmd->args = args_lst_to_array(arg_lst, tokens, shell);
	cmd->redirs = redirs;
	return (cmd);
}

t_cmds	*tokens_to_cmds(t_token_lst *tokens, t_shell *shell)
{
	t_cmds			*cmds;
	t_cmds			*new;
	t_cmd			*cmd;
	
	cmds = NULL;
	while (tokens)
	{
		cmd = cycle_until_pipe(tokens, shell);
		if (!cmd)
			//free cmds, error message
		new = lst_new_cmds(cmd);
		if (!new)
			//free
		ft_lstadd_back((t_list **)cmds, (t_list *)new);
		if (tokens)
			tokens = tokens->next;
	}
	return (cmds);
}


void	sort_list(t_list *list, int (*cmp)(int))

int cmp (int a int b)

sort_list(list, &cmp);