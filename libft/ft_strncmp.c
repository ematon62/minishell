/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ematon <ematon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 17:40:45 by ematon            #+#    #+#             */
/*   Updated: 2024/12/02 13:10:00 by ematon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	char		*str1;
	char		*str2;
	size_t		i;

	str1 = (char *)s1;
	str2 = (char *)s2;
	i = 0;
	while ((*str1 || *str2) && i < n)
	{
		if (*str1 != *str2)
			return ((unsigned char)*str1 - (unsigned char)*str2);
		str1++;
		str2++;
		i++;
	}
	return (0);
}

// int main(int argc, char **argv)
// {
// 	(void)argc;
// 	(void)argv;
// 	char *s1 = "abcdef";
//  	char *s2 = "abc\375xx";

// 	printf("%d\n", ft_strncmp(s1, s2, 5));
// 	printf("%d\n", strncmp(s1, s2, 5));
// }