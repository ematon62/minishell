/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ematon <ematon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 17:58:11 by ematon            #+#    #+#             */
/*   Updated: 2024/12/02 13:10:00 by ematon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ptr;
	size_t			i;

	ptr = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (*(ptr + i) == (unsigned char)c)
			return ((void *)(s + i));
		i++;
	}
	return (NULL);
}

// int main(void)
// {
// 	int	*ptr = malloc(sizeof(int) * 6);
// 	ptr[0] = 0;
// 	ptr[1] = ' ';
// 	ptr[2] = 2;
// 	ptr[3] = 3;
// 	ptr[4] = 4;
// 	ptr[5] = 5;
// 	printf("%p\n", ft_memchr(ptr, ' ', sizeof(int) * 6));
// 	printf("%p", memchr(ptr, ' ', sizeof(int) * 6));
// }