/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ematon <ematon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:21:09 by ematon            #+#    #+#             */
/*   Updated: 2024/12/02 13:10:00 by ematon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (dst[i])
		i++;
	if (size <= i)
		return (size + ft_strlen(src));
	while (src[j] && i + j + 1 < size)
	{
		dst[i + j] = src[j];
		j++;
	}
	dst[i + j] = '\0';
	while (src[j])
		j++;
	return (i + j);
}

// int main(void)
// {
// 	char dest[30]; memset(dest, 0, 30);
// 	char * src = (char *)"AAAAAAAAAAAAA";
// 	printf("%zu\n", strlcat(dest, src, 8));
// 	printf("%s", dest);
// }