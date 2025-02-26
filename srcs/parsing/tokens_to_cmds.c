/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_to_cmds.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ematon <ematon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 18:28:27 by ematon            #+#    #+#             */
/*   Updated: 2025/02/26 14:38:54 by ematon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	malloc_size(char ***args, t_token_lst *lst, t_token_lst *tokens, t_shell *sh)
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
		return (free_tokens_lst(tokens), free_shell(sh), free_tokens_lst(lst),
			exit_error("malloc"), 0);
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
	while (lst)
	{
		args[i] = ft_strdup(lst->token);
		if (!args[i])
			return (ft_free_toodee((void **)args), free_tokens_lst(lst),
				free_tokens_lst(tok), free_shell(sh),
				exit_error("malloc"), NULL);
		lst = lst->next;
		i++;
	}
	args[i] = NULL;
	return (args);
}

// t_cmds	*tokens_to_cmds(t_token_lst *tokens, t_shell *shell)
// {
// 	t_cmds			*cmds;
// 	t_cmd			*cmd;
// 	t_token_lst		*args_lst;
// 	t_redirections	*redirs;
	
// 	cmds = NULL;
// 	while (tokens)
// 	{
// 		redirs = NULL;
// 		args_lst = NULL;
// 		//cmd = new cmd
// 		while (tokens && tokens->type != IO_PIPE)
// 		{
// 			//Si redirection
// 			//	Ajouter a la liste des redirs
// 			//Sinon
// 			//	Ajouter a la liste des char *args
// 			tokens = tokens->next;
// 		}
// 		//cmd_node = new cmd_node avec cmd
// 		//Ajouter cmd_node a la liste des cmds
// 		if (tokens)
// 			tokens = tokens->next;
// 	}
// 	return (cmds);
// }
