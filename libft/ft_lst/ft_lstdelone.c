/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ematon <ematon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 15:15:49 by ematon            #+#    #+#             */
/*   Updated: 2025/01/12 21:02:21 by ematon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (lst != NULL)
	{
		del(lst->content);
		free(lst);
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
// 	ft_lstdelone(elem1, del);
// 	printf("%p", elem1);
// }