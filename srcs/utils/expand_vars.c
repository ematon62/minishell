/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ematon <ematon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 19:49:22 by ematon            #+#    #+#             */
/*   Updated: 2025/03/10 16:59:48 by ematon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*get_env_value(t_env_lst *env, const char *key)
{
	t_env_lst	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, key, ft_strlen(tmp->key) + 1) == 0)
		{
			if (tmp->value)
				return (ft_strdup(tmp->value));
			else
				return (ft_strdup(""));
		}
		tmp = tmp->next;
	}
	return (ft_strdup(""));
}

static char	*handle_dollar(char *input, size_t *i, t_shell *shell)
{
	char	*key;
	char	*value;
	size_t	start;

	(*i)++;
	start = *i;
	if (input[*i] == '?')
	{
		(*i)++;
		if (g_signal == 130)
			shell->exit_status = 130;
		return (ft_itoa(shell->exit_status));
	}
	while (ft_isalnum(input[*i]) || input[*i] == '_')
		(*i)++;
	key = ft_substr(input, start, *i - start);
	if (!key)
		return (NULL);
	value = get_env_value(shell->env, key);
	free(key);
	return (value);
}

static void	*process_char(char **result, char c)
{
	char	*tmp;
	char	ch[2];

	ch[0] = c;
	ch[1] = '\0';
	tmp = *result;
	*result = ft_strjoin(*result, ch);
	free(tmp);
	return (*result);
}

void	*process_expansion(char **result, char *token, size_t *i,
	t_shell *shell)
{
	char	*value;
	char	*tmp;

	value = handle_dollar(token, i, shell);
	if (!value)
		return (NULL);
	tmp = *result;
	*result = ft_strjoin(*result, value);
	if (!*result)
		return (free(value), free(tmp), NULL);
	return (free(tmp), free(value), (void *)1);
}

/*
token free au passage
*/
char	*expand_var(char *tok, t_shell *shell)
{
	char	*result;
	size_t	i;
	bool	in_single;
	bool	in_double;

	result = ft_strdup("");
	in_single = false;
	in_double = false;
	i = 0;
	while (result && tok[i])
	{
		if (tok[i] == '\'' && !in_double)
			in_single = !in_single;
		if (tok[i] == '\"' && !in_single)
			in_double = !in_double;
		if (tok[i] == '$' && tok[i + 1] && !in_single && tok[i + 1] != ' ')
		{
			if (!process_expansion(&result, tok, &i, shell))
				return (free(tok), NULL);
			continue ;
		}
		result = process_char(&result, tok[i]);
		i++;
	}
	return (free(tok), result);
}
