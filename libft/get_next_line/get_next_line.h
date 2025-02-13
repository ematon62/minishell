/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ematon <ematon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 11:25:53 by ematon            #+#    #+#             */
/*   Updated: 2024/12/02 11:55:07 by ematon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000000
# endif

char	*get_next_line(int fd);
char	*ft_charsearch(char *s, int c);
char	*ft_strjoin_mod(char *s1, char *s2, size_t n);
char	*ft_add_until_end_or_nl(char *line, char *buffer);
void	ft_shift_buffer(char *buffer, char *nl_pos);
ssize_t	ft_read_guard(int fd, char *buffer, char **line);

#endif