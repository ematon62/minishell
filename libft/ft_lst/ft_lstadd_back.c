/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 21:50:58 by marvin            #+#    #+#             */
/*   Updated: 2024/10/18 21:50:58 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (lst == NULL)
		lst = &new;
	else
	{
		last = ft_lstlast(*lst);
		if (last == NULL)
			*lst = new;
		else
			last->next = new;
	}
}

// int main (void)
// {
//     int a = 3;
//     int *content = &a;
// 	t_list *begin = NULL;
//     t_list  *elem1 = ft_lstnew(content);
//     t_list  *elem2 = ft_lstnew(content);
// 	t_list  *elem3 = ft_lstnew(content);
// 	ft_lstadd_back(&begin, elem1);
// 	ft_lstadd_back(&begin, elem2);
// 	ft_lstadd_back(&begin, elem3);
// 	printf("Adresses elems:\n");
// 	printf("1: %p\n", elem1);
// 	printf("2: %p\n", elem2);
// 	printf("3: %p\n", elem3);
// 	printf("Adresses nexts:\n");
// 	printf("next 1:%p\n", elem1->next);
// 	printf("next 2:%p\n", elem2->next);
// 	printf("next 3:%p\n", elem3->next);
// }
