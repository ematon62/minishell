/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ematon <ematon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 18:09:18 by ematon            #+#    #+#             */
/*   Updated: 2025/01/12 21:02:23 by ematon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*current;

	current = lst;
	while (current != NULL)
	{
		f(current->content);
		current = current->next;
	}
}

// void	f(void *content)
// {
// 	(void)content;
// 	printf("JE SUIS HEUREUX");
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
// 	ft_lstiter(elem1, &f);
// }