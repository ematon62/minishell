/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ematon <ematon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:48:00 by ematon            #+#    #+#             */
/*   Updated: 2024/12/02 13:10:00 by ematon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_belongs_to_str(char c, const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (c == str[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		i;
	int		j;
	int		k;

	j = ft_strlen(s1);
	i = 0;
	k = 0;
	while (s1[i] && ft_belongs_to_str(s1[i], set))
		i++;
	while (j > 0 && ft_belongs_to_str(s1[j - 1], set) && j > i)
		j--;
	str = malloc(sizeof(char) * (j - i + 1));
	if (str == NULL)
		return (NULL);
	while (s1[i] && i < j)
	{
		str[k] = s1[i];
		i++;
		k++;
	}
	str[k] = '\0';
	return (str);
}

// int main(int argc, char **argv)
// {
// 	(void)argc;
// 	char *str = ft_strtrim(argv[1], argv[2]);
// 	printf("%s", str);
// 	free(str);
// }