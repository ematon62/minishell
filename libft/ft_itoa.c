/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ematon <ematon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 12:28:36 by ematon            #+#    #+#             */
/*   Updated: 2024/12/02 13:10:00 by ematon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len_nb(int n)
{
	int	i;

	i = 0;
	if (!n)
		return (1);
	if (n < 0)
	{
		i++;
		n *= -1;
	}
	while (n != 0)
	{
		i++;
		n = n / 10;
	}
	return (i);
}

static char	*ft_fk_int_min(int n)
{
	char	*ptr;
	int		len;

	len = ft_len_nb(n);
	ptr = malloc((len + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	if (!n)
		ft_strlcpy(ptr, "0", len + 1);
	else
		ft_strlcpy(ptr, "-2147483648", len + 1);
	return (ptr);
}

char	*ft_itoa(int n)
{
	int		j;
	char	*str;

	if (!n || n == INT_MIN)
		return (ft_fk_int_min(n));
	j = ft_len_nb(n);
	str = malloc((j + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str[j] = '\0';
	if (n < 0)
	{
		str[0] = '-';
		n *= -1;
	}
	while (j >= 0)
	{
		j--;
		str[j] = (n % 10) + 48;
		n = n / 10;
		if (!n)
			break ;
	}
	return (str);
}

// int main(int argc, char **argv)
// {
// 	(void)argc;
// 	int	i = ft_atoi(argv[1]);
// 	printf("%s", ft_itoa(i));
// }
