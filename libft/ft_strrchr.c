/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ematon <ematon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 17:07:27 by ematon            #+#    #+#             */
/*   Updated: 2024/12/02 13:10:00 by ematon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int				i;
	unsigned char	uc;

	i = ft_strlen(s);
	uc = (unsigned char)c;
	if (uc == '\0')
		return ((char *)&s[i]);
	while (i >= 0)
	{
		if (s[i] == uc)
			return ((char *)&s[i]);
		i--;
	}
	return (NULL);
}

// int main(int argc, char **argv)
// {
// 	(void)argc;
// 	int i = 0;
// 	while (argv[1][i])
// 	{
// 		printf("%c %p\n", argv[1][i], &argv[1][i]);
// 		i++;
// 	}
// 	printf("%c %p\n", argv[1][i], &argv[1][i]);
// 	printf("%p\n", ft_strrchr(argv[1], argv[2][0]));
// }