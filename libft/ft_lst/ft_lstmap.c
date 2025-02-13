/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ematon <ematon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 18:15:59 by ematon            #+#    #+#             */
/*   Updated: 2025/01/12 21:02:29 by ematon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*current;
	t_list	*new_lst;
	t_list	*start;
	t_list	*temp;

	if (!lst)
		return (NULL);
	current = lst;
	start = NULL;
	while (current)
	{
		temp = f(current->content);
		if (temp == NULL)
			return (ft_lstclear(&start, del), NULL);
		new_lst = ft_lstnew(temp);
		if (!new_lst)
		{
			del(temp);
			ft_lstclear(&start, del);
			return (NULL);
		}
		ft_lstadd_back(&start, new_lst);
		current = current->next;
	}
	return (start);
}

// static void	del(void *content)
// {
// 	free(content);
// }

// static void	*f(void *content)
// {
// 	char *caca = malloc(sizeof(char));
// 	caca[0] = ((char *)content)[0] + 1;
// 	return caca;
// }

// int main (void)
// {
//     // t_list  *elem1 = ft_lstnew("1");
// 	// t_list  *elem2 = ft_lstnew("2");
// 	// t_list  *elem3 = ft_lstnew("3");
// 	// ft_lstadd_back(&elem1, elem2);
// 	// ft_lstadd_back(&elem1, elem3);
// 	t_list *fe = ft_lstmap(NULL, &f, &del);
// 	(void)fe;
// 	// printf("%s", (char *)fe->content);
// 	// fe = fe->next;
// 	// printf("%s", (char *)fe->content);
// 	// fe = fe->next;
// 	// printf("%s", (char *)fe->content);
// 	// fe = fe->next;
// 	// free(fe);
// }
