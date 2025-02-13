/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ematon <ematon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 18:25:30 by ematon            #+#    #+#             */
/*   Updated: 2024/12/02 13:09:12 by ematon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t		i;
	char		*ptr;

	ptr = (char *)s;
	i = 0;
	while (i < n)
	{
		*(ptr + i) = 0;
		i++;
	}
}

// int main(void)
// {
// 	int tab1[] = {1, 2, 3, 4};
// 	bzero(tab1, sizeof(tab1));
// 	int i = 0;
// 	while (i < 4)
// 	{
// 		printf("%d %#08x\n", tab1[i], tab1[i]);
// 		i++;
// 	}
// }