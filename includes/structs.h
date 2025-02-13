/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ematon <ematon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 10:50:55 by ematon            #+#    #+#             */
/*   Updated: 2025/02/14 16:42:59 by ematon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "utils.h"

typedef struct s_env_lst
{
	struct s_env_lst	*next;
	char				*key;
	char				*value;
	bool				is_env;
}	t_env_lst;

typedef struct s_shell
{
	t_env_lst	*env;
	char		*path;
	int			exit_status;
	
}	t_shell;

typedef enum e_type
{
	IS_INREDIR,
	IS_HEREDOC,
	IS_TRUNCAT,
	IS_APPEND
}	t_type;

typedef struct s_redirection
{
	struct s_redirection	*next;
	t_type					type;
	char					*target;
}	t_redirections;

typedef struct s_cmd
{
	char			**args;
	t_redirections	*redirs;
	char			*in;
	char			*out;
}	t_cmd;

typedef struct s_cmds
{
	struct s_cmds	*next;
	t_cmd			cmd;
}	t_cmds;

#endif