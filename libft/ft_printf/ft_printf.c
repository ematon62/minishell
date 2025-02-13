/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ematon <ematon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 14:35:01 by ematon            #+#    #+#             */
/*   Updated: 2025/01/08 14:51:47 by ematon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ptr;
	size_t			i;

	ptr = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (*(ptr + i) == (unsigned char)c)
			return ((void *)(s + i));
		i++;
	}
	return (NULL);
}

void	ft_handle_conv(va_list arg, char specifier, int *nb)
{
	if (specifier == 'c')
		ft_handle_char(arg, nb);
	else if (specifier == 's')
		ft_handle_str(arg, nb);
	else if (specifier == 'p')
		ft_handle_ptr(arg, nb);
	else if (specifier == 'd' || specifier == 'i')
		ft_handle_int(arg, nb);
	else if (specifier == 'u')
		ft_handle_hex_ud(arg, nb, -1);
	else if (specifier == 'x')
		ft_handle_hex_ud(arg, nb, 0);
	else if (specifier == 'X')
		ft_handle_hex_ud(arg, nb, 1);
	else if (specifier == '%')
		ft_putchar_ptr('%', nb);
}

int	ft_aprintf(char const *format, va_list arg)
{
	int	nb_printed;
	int	i;

	i = 0;
	nb_printed = 0;
	while (format[i])
	{
		if (format[i] != '%')
		{
			write(1, &format[i], 1);
			nb_printed += 1;
		}
		else
		{
			if (ft_memchr("cspdiuxX%", format[i + 1], 9))
			{
				ft_handle_conv(arg, format[i + 1], &nb_printed);
				i++;
			}
			else
				return (-1);
		}
		i++;
	}
	return (nb_printed);
}

int	ft_printf(char const *format, ...)
{
	int			nb_printed;
	va_list		arg;

	va_start(arg, format);
	nb_printed = ft_aprintf(format, arg);
	va_end(arg);
	return (nb_printed);
}

// int main(void)
// {
// 	printf("Test 1\n");
// 	char c = 's';
// 	char *s = "caca";
// 	int i = -42;
// 	int *p = &i;
// 	int i1 = ft_printf("%c %s %p %d %i %x %X %u\n", c, s, p, i, i, i, i, i);
// 	int i2 = printf("%c %s %p %d %i %x %X %u\n", c, s, p, i, i, i, i, i);
// 	printf("%d %d\n", i1, i2);
// 	printf("Test 2\n");
// 	i1 = ft_printf("bordel %\n");
// 	i2 = printf("bordel %\n");
// 	printf("%d %d\n", i1, i2);
// 	printf("Test 3\n");
// 	i1 = ft_printf("bordel\n%");
// 	i2 = printf("bordel\n%");
// 	printf("%d %d\n", i1, i2);
// 	printf("Test 4\n");
// 	i1 = ft_printf("%d\n");
// 	i2 = printf("%d\n");
// 	printf("%d %d\n", i1, i2);
// }