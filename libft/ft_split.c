/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ematon <ematon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 15:47:34 by ematon            #+#    #+#             */
/*   Updated: 2024/12/02 13:10:00 by ematon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char const	*ft_go_through_separators(char const *str, char sep)
{
	while (*str && *str == sep)
		str++;
	return (str);
}

static char const	*ft_strsubcpy(char const *str, char **tab, int i, char sep)
{
	int	k;

	k = 0;
	tab[i] = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!tab[i])
	{
		while (i--)
			free(tab[i]);
		free(tab);
		return (NULL);
	}
	while (*str && *str != sep)
	{
		tab[i][k] = *str;
		k++;
		str++;
	}
	tab[i][k] = '\0';
	return (str);
}

static void	*ft_free_for_all(char **tab, char **split, int j, int nb)
{
	int	i;

	i = 0;
	if (split)
	{
		while (i < j)
		{
			free(split[i]);
			i++;
		}
		free(split);
	}
	i = j;
	while (i < nb)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

static char	**ft_memory_reduce_split(char **tab, int nb)
{
	int		j;
	char	**split;
	size_t	n;

	j = 0;
	split = malloc(sizeof(char *) * (nb + 1));
	if (!split)
		return (ft_free_for_all(tab, split, j, nb));
	while (tab[j] != NULL)
	{
		n = ft_strlen(tab[j]);
		split[j] = malloc(sizeof(char) * (n + 1));
		if (!split[j])
			return (ft_free_for_all(tab, split, j, nb));
		ft_strlcpy(split[j], tab[j], n + 1);
		free(tab[j]);
		j++;
	}
	split[j] = NULL;
	free(tab);
	return (split);
}

char	**ft_split(char const *s, char c)
{
	char const	*str;
	char		**tab;
	int			i;

	i = 0;
	tab = malloc(sizeof(char *) * (ft_strlen(s) + 1));
	if (tab == NULL)
		return (tab);
	while (*s)
	{
		str = s;
		str = ft_go_through_separators(s, c);
		if (*str)
		{
			str = ft_strsubcpy(str, tab, i, c);
			if (!str)
				return (NULL);
			i++;
		}
		s = str;
	}
	tab[i] = NULL;
	return (ft_memory_reduce_split(tab, i));
}

// int main(void)
// {
// 	char **tab = ft_split("hello!", ' ');
// 	free(*tab);
// 	free(tab);
// }