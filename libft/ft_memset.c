/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ematon <ematon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 17:35:04 by ematon            #+#    #+#             */
/*   Updated: 2024/12/02 13:10:00 by ematon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;
	char	*ptr;

	i = 0;
	ptr = (char *)s;
	while (i < n)
	{
		ptr[i] = (unsigned char)c ;
		i++;
	}
	return (s);
}

// int main(void)
// {
// 	int tab1[] = {1, 2, 3, 4};
// 	int tab2[] = {1, 2, 3, 4};
// 	memset(tab1, 20, sizeof(tab1));
// 	ft_memset(tab2, 20, sizeof(tab2));
// 	size_t i = 0;
// 	while (i < 4)
// 	{
// 		printf("%d %#10x\n", tab1[i], tab1[i]);
// 		printf("%d %#10x\n", tab2[i], tab2[i]);
// 		printf("\n");
// 		i++;
// 	}
// }