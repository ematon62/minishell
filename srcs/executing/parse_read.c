/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_read.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adcisse <adcisse@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-18 15:25:00 by adcisse           #+#    #+#             */
/*   Updated: 2025-02-18 15:25:00 by adcisse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executing.h"

char	*get_env_value(t_env_lst *env, const char *key)
{
	t_env_lst	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, key, ft_strlen(key) + 1) == 0)
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
		return (ft_itoa(shell->exit_status));
	}
	while (ft_isalnum(input[*i]) || input[*i] == '_')
		(*i)++;
	key = ft_substr(input, start, *i - start);
	value = get_env_value(shell->env, key);
	free(key);
	return (value);
}

static void	process_char(char **result, char c)
{
	char	*tmp;
	char	ch[2];

	ch[0] = c;
	ch[1] = '\0';
	tmp = *result;
	*result = ft_strjoin(*result, ch);
	free(tmp);
}

void	process_expansion(char **result, char *token, size_t *i, t_shell *shell)
{
	char	*value;
	char	*tmp;

	value = handle_dollar(token, i, shell);
	tmp = *result;
	*result = ft_strjoin(*result, value);
	free(tmp);
	free(value);
}

char	*expand_var(char *token, t_shell *shell)
{
	char	*result;
	size_t	i;
	bool	in_single;
	bool	in_double;

	result = ft_strdup("");
	in_single = false;
	in_double = false;
	i = 0;
	while (token[i])
	{
		if (token[i] == '\'' && !in_double)
			in_single = !in_single;
		if (token[i] == '"' && !in_single)
			in_double = !in_double;
		if (token[i] == '$' && !in_single)
		{
			process_expansion(&result, token, &i, shell);
			continue ;
		}
		process_char(&result, token[i]);
		i++;
	}
	return (result);
}
