/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ematon <ematon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 14:40:24 by ematon            #+#    #+#             */
/*   Updated: 2024/11/25 15:06:29 by ematon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h>
# include <stdarg.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <limits.h>

int			ft_printf(char const *s, ...);
int			ft_aprintf(char const *s, va_list arg);
void		ft_handle_conv(va_list arg, char specifier, int *nb);
void		ft_handle_char(va_list arg, int *nb);
void		ft_handle_str(va_list arg, int *nb);
void		ft_handle_int(va_list arg, int *nb);
void		ft_handle_ptr(va_list arg, int *nb);
void		ft_handle_hex_ud(va_list arg, int *nb, int capitalize);
void		ft_putchar_ptr(char c, int *nb);
void		ft_putstr_ptr(const char *s, int *nb);
void		ft_putnbr_ptr(int n, int *nb);
void		ft_putnbr_unsigned(unsigned int printed, int *nb);
void		ft_putnbr_hexa(long unsigned int printed, int *nb, int capitalize);

#endif