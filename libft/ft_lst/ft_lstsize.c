/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 21:29:57 by marvin            #+#    #+#             */
/*   Updated: 2024/10/18 21:29:57 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_lstsize(t_list *lst)
{
	int		i;
	t_list	*temp;

	i = 0;
	temp = lst;
	while (temp != NULL)
	{
		temp = temp->next;
		i++;
	}
	return (i);
}

// int main (void)
// {
//     int a = 1;
// 	int b = 2;
// 	int c = 3;
//     int *contenta = &a;
// 	int *contentb = &b;
// 	int *contentc = &c;
//     t_list  *elem1 = ft_lstnew(contenta);
//     t_list  *elem2 = ft_lstnew(contentb);
// 	t_list  *elem3 = ft_lstnew(contentc);
// 	ft_lstadd_front(&elem3, elem2);
// 	ft_lstadd_front(&elem2, elem1);
//     printf("%d", ft_lstsize(NULL));
// 	free(elem1);
// 	free(elem2);
// 	free(elem3);
// }