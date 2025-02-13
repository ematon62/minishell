/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handling_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ematon <ematon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:43:32 by ematon            #+#    #+#             */
/*   Updated: 2025/01/08 14:51:43 by ematon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putchar_ptr(char c, int *nb)
{
	write(1, &c, 1);
	*nb += 1;
}

void	ft_putstr_ptr(const char *s, int *nb)
{
	int	i;

	i = 0;
	while (s[i])
	{
		ft_putchar_ptr(s[i], nb);
		i++;
	}
}

void	ft_putnbr_ptr(int n, int *nb)
{
	int	i;

	i = n;
	if (i == INT_MIN)
	{
		ft_putstr_ptr("-2147483648", nb);
		return ;
	}
	if (i < 0)
	{
		ft_putchar_ptr('-', nb);
		i = i * (-1);
	}
	if (i < 10)
		ft_putchar_ptr(i + 48, nb);
	else
	{
		ft_putnbr_ptr(i / 10, nb);
		ft_putchar_ptr((i % 10) + 48, nb);
	}
}

void	ft_putnbr_unsigned(unsigned int printed, int *nb)
{
	if (printed < 10)
		ft_putchar_ptr('0' + printed, nb);
	else
	{
		ft_putnbr_unsigned(printed / 10, nb);
		ft_putnbr_unsigned(printed % 10, nb);
	}
}

void	ft_putnbr_hexa(long unsigned int printed, int *nb, int capitalize)
{
	if (printed < 10)
		ft_putchar_ptr('0' + printed, nb);
	else if (printed < 16)
		ft_putchar_ptr('a' + (printed - 10) - capitalize * 32, nb);
	else
	{
		ft_putnbr_hexa(printed / 16, nb, capitalize);
		ft_putnbr_hexa(printed % 16, nb, capitalize);
	}
}
