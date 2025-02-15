/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ematon <ematon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 19:40:24 by ematon            #+#    #+#             */
/*   Updated: 2025/02/15 14:07:05 by ematon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "utils.h"

# define MATCHING_ERR "bash: unexpected EOF while looking for matching quote\n"

typedef enum e_token
{
	WORD,
	IO_IN,
	IO_OUT,
	IO_HEREDOC,
	IO_APPEND,
	IO_PIPE
}	t_token;

typedef struct s_tokens
{
	
};


//Shell
t_shell	*init_shell(char **envp);

//Parsing
t_cmds	*parse(char *input, t_shell *shell);
bool	is_unclosed_quote(char *input);

#endif