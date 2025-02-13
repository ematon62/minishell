/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ematon <ematon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 21:08:52 by ematon            #+#    #+#             */
/*   Updated: 2024/12/02 13:09:16 by ematon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void		*ptr;
	size_t		i;

	i = 0;
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