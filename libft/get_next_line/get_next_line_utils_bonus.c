/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ematon <ematon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 11:02:18 by ematon            #+#    #+#             */
/*   Updated: 2024/12/02 13:10:59 by ematon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

ssize_t	ft_read_guard(int fd, char *buffer_fd, char **line)
{
	ssize_t	nb_bytes_read;

	nb_bytes_read = read(fd, buffer_fd, BUFFER_SIZE);
	if (nb_bytes_read < 0)
	{
		free(*line);
		*line = NULL;
	}
	return (nb_bytes_read);
}

char	*ft_charsearch(char *s, int c)
{
	int				i;
	unsigned char	uc;

	i = 0;
	uc = (unsigned char)c;
	while (s[i])
	{
		if (s[i] == uc)
			return ((char *)&s[i]);
		i++;
	}
	if (s[i] == uc)
		return ((char *)&s[i]);
	else
		return (NULL);
}

char	*ft_strjoin_mod(char *s1, char *s2, size_t n)
{
	char		*str;
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	while (s1[i])
		i++;
	str = malloc(sizeof(char) * (i + n + 1));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j] && j < n)
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = 0;
	return (str);
}

char	*ft_add_until_end_or_nl(char *line, char *buffer_fd)
{
	char	*nl_pos;
	char	*new_line;

	if (!buffer_fd)
		return (NULL);
	nl_pos = ft_charsearch(buffer_fd, '\n');
	if (!nl_pos && !line)
		return (ft_strjoin_mod("", buffer_fd, BUFFER_SIZE));
	else if (!nl_pos && line)
	{
		new_line = ft_strjoin_mod(line, buffer_fd, BUFFER_SIZE);
		free(line);
		return (new_line);
	}
	else if (nl_pos && !line)
	{
		return (ft_strjoin_mod("", buffer_fd, nl_pos - buffer_fd + 1));
	}
	else
	{
		new_line = ft_strjoin_mod(line, buffer_fd, nl_pos - buffer_fd + 1);
		free(line);
		return (new_line);
	}
}

void	ft_shift_buffer(char *buffer_fd, char *nl_pos)
{
	int		j;
	int		i;

	i = 0;
	if (!nl_pos || !buffer_fd[nl_pos - buffer_fd + 1])
	{
		while (i < BUFFER_SIZE + 1)
		{
			buffer_fd[i] = 0;
			i++;
		}
	}
	else
	{
		j = nl_pos - buffer_fd + 1;
		while (buffer_fd[j])
		{
			buffer_fd[i] = buffer_fd[j];
			buffer_fd[j] = 0;
			i++;
			j++;
		}
		buffer_fd[i] = 0;
	}
}
