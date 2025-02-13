/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ematon <ematon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 11:11:07 by ematon            #+#    #+#             */
/*   Updated: 2024/12/02 13:10:49 by ematon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static char	buffer[MAX_FD + 1][BUFFER_SIZE + 1];
	char		*line;
	ssize_t		nb_bytes_read;

	if (BUFFER_SIZE <= 0 || MAX_FD < 1 || fd < 0 || fd > MAX_FD)
		return (NULL);
	line = NULL;
	while (buffer[fd][0])
	{
		line = ft_add_until_end_or_nl(line, buffer[fd]);
		ft_shift_buffer(buffer[fd], ft_charsearch(buffer[fd], '\n'));
		if (!line || ft_charsearch(line, '\n'))
			return (line);
	}
	nb_bytes_read = ft_read_guard(fd, buffer[fd], &line);
	while (nb_bytes_read > 0)
	{
		line = ft_add_until_end_or_nl(line, buffer[fd]);
		ft_shift_buffer(buffer[fd], ft_charsearch(buffer[fd], '\n'));
		if (!line || ft_charsearch(line, '\n'))
			return (line);
		nb_bytes_read = ft_read_guard(fd, buffer[fd], &line);
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