/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ematon <ematon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 11:56:27 by ematon            #+#    #+#             */
/*   Updated: 2024/12/02 13:10:00 by ematon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int	i;

	i = n;
	if (i == INT_MIN)
	{
		ft_putstr_fd("-2147483648", fd);
		return ;
	}
	if (i < 0)
	{
		ft_putchar_fd('-', fd);
		i = i * (-1);
	}
	if (i < 10)
	{
		ft_putchar_fd(i + 48, fd);
	}
	else
	{
		ft_putnbr_fd(i / 10, fd);
		ft_putchar_fd((i % 10) + 48, fd);
	}
}

// int main(void)
// {
// 	int fd = open("test_file", O_WRONLY);
// 	ft_putnbr_fd(INT_MIN - 1, fd);
// 	close(fd);
// }