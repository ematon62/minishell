/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cisse <cisse@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 11:43:26 by ematon            #+#    #+#             */
/*   Updated: 2025/03/01 15:58:36 by cisse            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
}

// int main(void)
// {
// 	int fd = open("test_file", O_WRONLY);
// 	ft_putstr_fd("", fd);
// 	close(fd);
// }