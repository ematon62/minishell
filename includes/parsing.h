/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ematon <ematon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 19:40:24 by ematon            #+#    #+#             */
/*   Updated: 2025/02/26 13:25:08 by ematon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "utils.h"

# define MATCHING "bash: unexpected EOF while looking for matching quote\n"
# define UNEXPECTED_EOF "bash: syntax error: unexpected end of file\nexit\n"
# define SYNTAX "bash: syntax error\n"

//Shell
t_shell		*init_shell(char **envp);

//Lexer
t_token_lst	*lexer(char *input, t_shell *shell);
t_token_lst	*remove_spaces(char *input, t_shell *shell);

//Parsing
t_cmds		*parse(char *input, t_shell *shell);
bool		is_unclosed_quote(char *input);
void		change_quote_status(bool *quote);
bool		complete_pipe(t_token_lst *tokens, t_shell *shell);
bool		check_tokens(t_token_lst *tokens);

char		*expand_var(char *token, t_shell *shell);

char		**args_lst_to_array(t_token_lst *lst, t_token_lst *tok, t_shell *sh);

#endif