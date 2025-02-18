/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ematon <ematon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 10:50:55 by ematon            #+#    #+#             */
/*   Updated: 2025/02/18 20:21:27 by ematon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <stdbool.h>

typedef enum e_token
{
	WORD,
	IO_IN,
	IO_OUT,
	IO_HEREDOC,
	IO_APPEND,
	IO_PIPE,
	UNDEFINED
}	t_token;

//NULL si type = PIPE, IO_IN, IO_OUT, IO_APPEND, IO_HEREDOC
typedef struct s_token_lst
{
	struct s_token_lst	*next;
	char				*token;
	t_token				type;
}	t_token_lst;

typedef struct s_env_lst
{
	struct s_env_lst	*next;
	char				*key;
	char				*value;
	bool				is_env;
}	t_env_lst;

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
	t_cmd			*cmd;
}	t_cmds;

typedef struct s_shell
{
	t_env_lst	*env;
	t_cmds		*cmds;
	int			exit_status;
}	t_shell;

#endif