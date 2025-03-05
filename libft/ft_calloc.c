/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cisse <cisse@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 21:08:52 by ematon            #+#    #+#             */
/*   Updated: 2025/03/01 15:58:52 by cisse            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void		*ptr;

	if (!nmemb && !size && ((nmemb * size) / size != nmemb))
		return (NULL);
	ptr = malloc(nmemb * size);
	if (ptr == NULL)
		return (NULL);
	return (ft_memset(ptr, 0, nmemb * size));
}

// int main(void)
// {
// 	char *d2 = ft_calloc(INT_MAX, 2);
// 	printf("%p", d2);
// }