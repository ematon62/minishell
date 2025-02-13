/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ematon <ematon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 11:43:26 by ematon            #+#    #+#             */
/*   Updated: 2025/02/07 19:11:12 by ematon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	write(fd, s, ft_strlen(s));
}

// int main(void)
// {
// 	int fd = open("test_file", O_WRONLY);
// 	ft_putstr_fd("", fd);
// 	close(fd);
// }