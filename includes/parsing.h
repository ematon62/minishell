/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ematon <ematon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 19:40:24 by ematon            #+#    #+#             */
/*   Updated: 2025/03/10 15:18:10 by ematon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "utils.h"

# define MATCHING "bash: unexpected EOF while looking for matching quote\n"
# define UNEXPECTED_EOF "bash: syntax error: unexpected end of file\nexit\n"
# define SYNTAX "bash: syntax error\n"

//Shell
t_shell		*init_shell(char **envp, int argc, char **argv);

//Lexer
t_token_lst	*lexer(char *input);
t_token_lst	*remove_spaces(char *input);

//Parsing
t_cmds		*parse(char *input, t_shell *shell);
bool		is_unclosed_quote(char *input);
bool		complete_pipe(t_token_lst *tokens, t_shell *shell);
bool		check_tokens(t_token_lst *tokens);

void		*complete_cmd(t_token_lst *tokens, t_redirections **redirs,
				t_token_lst **args);
t_token_lst	*cycle_until_pipe(t_token_lst *tokens, t_cmd *cmd);
t_cmds		*tokens_to_cmds(t_token_lst *tokens);
char		**args_lst_to_array(t_token_lst *lst);

#endif