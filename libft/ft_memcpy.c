/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ematon <ematon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 18:49:12 by ematon            #+#    #+#             */
/*   Updated: 2024/12/02 13:10:00 by ematon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t		i;
	char		*ptr1;
	char		*ptr2;

	i = 0;
	ptr1 = (char *)dest;
	ptr2 = (char *)src;
	if (!dest && !src)
		return (NULL);
	while (i < n)
	{
		*(ptr1 + i) = *(ptr2 + i);
		i++;
	}
	return (dest);
}

// int main(void)
// {
// 	int tab[] = {1, 2, 3, 4};
// 	int tab2[] = {4, 3, 2, 1};
// 	int tab1[] = {0, 0, 0, 0};
// 	ft_memcpy(tab1, tab, sizeof(tab));
// 	int i = -5;
// 	while (i < 15)
// 	{
// 		printf("%d\n", tab1[i]);
// 		i++;
// 	}
// }