/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ematon <ematon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:11:59 by ematon            #+#    #+#             */
/*   Updated: 2024/12/02 13:10:00 by ematon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		n1;
	int		n2;

	n1 = ft_strlen(s1);
	n2 = ft_strlen(s2);
	str = malloc(sizeof(char) * (n1 + n2 + 1));
	if (str == NULL)
		return (NULL);
	str[0] = '\0';
	ft_strlcat(str, s1, n1 + n2 + 1);
	ft_strlcat(str, s2, n1 + n2 + 1);
	return (str);
}

// int main(int argc, char **argv)
// {
// 	(void)argc;
// 	char *s = ft_strjoin(argv[1], argv[2]);
// 	printf("%s", s);
// 	free(s);
// }