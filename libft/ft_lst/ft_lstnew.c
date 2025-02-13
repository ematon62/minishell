/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 21:04:42 by marvin            #+#    #+#             */
/*   Updated: 2024/10/18 21:04:42 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*elem;

	elem = malloc(sizeof(t_list));
	if (elem == NULL)
		return (NULL);
	elem->content = content;
	elem->next = NULL;
	return (elem);
}

// int main(void)
// {
//     t_list  *elem;
//     int a = 3;
//     int *content = &a;
//     elem = ft_lstnew(content);
//     printf("%d\n", *(int *)elem->content);
//     printf("%p", elem->next);
// 	free(elem);
// }