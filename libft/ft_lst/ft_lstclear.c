/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ematon <ematon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 15:32:33 by ematon            #+#    #+#             */
/*   Updated: 2025/01/12 21:02:18 by ematon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;
	t_list	*current;

	if (lst != NULL)
	{
		current = *lst;
		while (current != NULL)
		{
			temp = current->next;
			ft_lstdelone(current, del);
			current = temp;
		}
		*lst = NULL;
	}
}

// void	del(void *content)
// {
// 	content = 0;
// }

// int main (void)
// {
//     int a = 3;
//     int *content = &a;
//     t_list  *elem1 = ft_lstnew(content);
//     t_list  *elem2 = ft_lstnew(content);
// 	t_list  *elem3 = ft_lstnew(content);
// 	t_list  *elem4 = ft_lstnew(content);
// 	ft_lstadd_back(&elem1, elem2);
// 	ft_lstadd_back(&elem1, elem3);
// 	ft_lstadd_back(&elem1, elem4);
// 	ft_lstclear(&elem1, &del);
// }