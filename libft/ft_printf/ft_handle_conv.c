/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_conv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ematon <ematon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 10:43:32 by ematon            #+#    #+#             */
/*   Updated: 2025/01/08 14:51:39 by ematon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_handle_char(va_list arg, int *nb)
{
	unsigned char	c;

	c = (unsigned char)va_arg(arg, int);
	ft_putchar_ptr(c, nb);
}

void	ft_handle_str(va_list arg, int *nb)
{
	const char	*s;
	int			i;
	int			n;

	i = 0;
	n = 0;
	s = (const char *)va_arg(arg, const char *);
	if (!s)
	{
		ft_putstr_ptr("(null)", nb);
		return ;
	}
	ft_putstr_ptr(s, nb);
}

void	ft_handle_int(va_list arg, int *nb)
{
	int		printed;
	int		n;

	n = 0;
	printed = (int)va_arg(arg, int);
	ft_putnbr_ptr(printed, nb);
}

void	ft_handle_ptr(va_list arg, int *nb)
{
	long unsigned int	printed;

	printed = (long unsigned int)va_arg(arg, void *);
	if (!printed)
	{
		ft_putstr_ptr("(nil)", nb);
		return ;
	}
	ft_putstr_ptr("0x", nb);
	ft_putnbr_hexa(printed, nb, 0);
}

void	ft_handle_hex_ud(va_list arg, int *nb, int capitalize)
{
	unsigned int	printed;

	printed = (unsigned int)va_arg(arg, unsigned int);
	if (capitalize < 0)
		ft_putnbr_unsigned(printed, nb);
	else
		ft_putnbr_hexa(printed, nb, capitalize);
}

// int main(void)
// {
// 	int nb = 0;
// 	int *ptr = &nb;
// 	ft_putnbr_unsigned(UINT_MAX, ptr);
// 	printf("\n%d", nb);
// }