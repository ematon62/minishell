/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ematon <ematon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 11:11:07 by ematon            #+#    #+#             */
/*   Updated: 2024/12/02 13:11:07 by ematon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;
	ssize_t		nb_bytes_read;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	line = NULL;
	while (buffer[0])
	{
		line = ft_add_until_end_or_nl(line, buffer);
		ft_shift_buffer(buffer, ft_charsearch(buffer, '\n'));
		if (!line || ft_charsearch(line, '\n'))
			return (line);
	}
	nb_bytes_read = ft_read_guard(fd, buffer, &line);
	while (nb_bytes_read > 0)
	{
		line = ft_add_until_end_or_nl(line, buffer);
		ft_shift_buffer(buffer, ft_charsearch(buffer, '\n'));
		if (!line || ft_charsearch(line, '\n'))
			return (line);
		nb_bytes_read = ft_read_guard(fd, buffer, &line);
	}
	return (line);
}

// int main(void)
// {
// 	int fd = open("testfile.txt", O_RDONLY);
// 	char *line = get_next_line(fd);
// 	printf("%s", line);
// 	free(line);
// 	line = get_next_line(fd);
// 	printf("%s", line);
// 	free(line);
// 	line = get_next_line(fd);
// 	printf("%s", line);
// 	free(line);
// 	line = get_next_line(fd);
// 	printf("%s", line);
// 	free(line);
// 	line = get_next_line(fd);
// 	printf("%s", line);
// 	free(line);
// 	line = get_next_line(fd);
// 	printf("%s", line);
// 	free(line);
// 	line = get_next_line(fd);
// 	printf("%s", line);
// 	free(line);
// 	line = get_next_line(fd);
// 	printf("%s", line);
// 	free(line);
// 	line = get_next_line(fd);
// 	printf("%s", line);
// 	free(line);
// 	line = get_next_line(fd);
// 	printf("%s", line);
// 	free(line);
// }