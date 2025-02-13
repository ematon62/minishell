/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ematon <ematon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:47:53 by ematon            #+#    #+#             */
/*   Updated: 2024/12/02 13:10:00 by ematon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_alloc_substr(unsigned int start, size_t len, size_t n)
{
	char		*substr;
	size_t		j;
	size_t		i;

	i = 0;
	j = start;
	while (j < n && i < len)
	{
		i++;
		j++;
	}
	substr = malloc(sizeof(char) * (i + 1));
	if (substr == NULL)
		return (NULL);
	return (substr);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*substring;
	size_t		i;
	size_t		j;
	size_t		n;

	n = ft_strlen(s);
	i = 0;
	j = start;
	substring = ft_alloc_substr(start, len, n);
	if (substring == NULL)
		return (NULL);
	while (j < n && i < len)
	{
		substring[i] = s[j];
		j++;
		i++;
	}
	substring[i] = '\0';
	return (substring);
}

// int main(int argc, char **argv)
// {
// 	(void)argc;
// 	(void)argv;
// 	char *d = ft_substr("hola", 6, 4);
// 	printf("%zu", ft_strlen(d));
// 	printf("%s", d);
// 	free(d);
// 	return (0);
// }