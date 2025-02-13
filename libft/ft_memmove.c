/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ematon <ematon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 19:08:18 by ematon            #+#    #+#             */
/*   Updated: 2024/12/02 13:10:00 by ematon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*ptrd;
	char		*ptrs;

	ptrd = (char *)dest;
	ptrs = (char *)src;
	if (!dest && !src)
		return (NULL);
	if (ptrd <= ptrs)
	{
		while (n--)
			*ptrd++ = *ptrs++;
	}
	else
	{
		ptrd += n - 1;
		ptrs += n - 1;
		while (n--)
			*ptrd-- = *ptrs--;
	}
	return (dest);
}
