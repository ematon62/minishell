/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 21:44:00 by marvin            #+#    #+#             */
/*   Updated: 2024/10/18 21:44:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*last;

	last = lst;
	if (last == NULL)
		return (NULL);
	while (last->next != NULL)
		last = last->next;
	return (last);
}

// int main (void)
// {
//     t_list  *elem1 = ft_lstnew("1");
//     t_list  *elem2 = ft_lstnew("2");
// 	t_list  *elem3 = ft_lstnew("3");
// 	t_list	**elem = &elem1;
//     printf("%p\n", elem1);
//     printf("%p\n", elem2);
// 	printf("%p\n", elem3);
// 	ft_lstadd_front(elem, elem2);
// 	ft_lstadd_front(elem, elem3);
// 	printf("%s\n", (char *)elem1->content);
//     printf("%s\n", (char *)elem2->content);
// 	printf("%s\n", (char *)elem3->content);
// }