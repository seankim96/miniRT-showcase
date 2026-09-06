/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungjuk <seungjuk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 19:05:05 by seungjuk          #+#    #+#             */
/*   Updated: 2025/02/21 17:01:11 by seungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stdio.h"

static char	*ft_strjoin_free(char *s, char *append)
{
	char	*c;
	size_t	s_len;
	size_t	a_len;
	size_t	i;

	i = 0;
	s_len = ft_strlen(s);
	a_len = ft_strlen(append);
	c = (char *)malloc(s_len + a_len + 1);
	if (!c)
		return (NULL);
	while (i < s_len)
	{
		c[i] = s[i];
		i++;
	}
	while (i < s_len + a_len)
	{
		c[i] = append[i - s_len];
		i++;
	}
	c[i] = '\0';
	return (free(s), free(append), c);
}

static char	*read_recursive(char *c, int fd, t_buff *b)
{
	ssize_t	i;
	char	*s;

	b->byte_read = read(fd, b->buffer, BUFFER_SIZE);
	b->buffer[b->byte_read] = '\0';
	if (b->byte_read <= 0)
		return (c);
	i = b->buffer_read;
	while (i < b->byte_read && b->buffer[i] != '\n')
		i++;
	s = ft_substr(b->buffer, b->buffer_read, i + 1);
	s = ft_strjoin_free(c, s);
	if (!s)
		return (NULL);
	if (b->buffer[i] == '\n')
		i++;
	b->buffer_read = i;
	if (b->buffer_read == b->byte_read)
	{
		b->buffer_read = 0;
		if (b->buffer[i - 1] != '\n')
			s = read_recursive(s, fd, b);
	}
	return (s);
}

char	*get_next_line(int fd)
{
	static t_buff	buffer;
	ssize_t			i;
	char			*s;

	if (buffer.buffer_read == 0)
		buffer.byte_read = read(fd, buffer.buffer, BUFFER_SIZE);
	buffer.buffer[buffer.byte_read] = '\0';
	if (buffer.byte_read <= 0)
		return (NULL);
	i = buffer.buffer_read;
	while (i < buffer.byte_read && buffer.buffer[i] != '\n')
		i++;
	s = ft_substr(buffer.buffer, \
	buffer.buffer_read, i + 1 - buffer.buffer_read);
	if (buffer.buffer[i] == '\n')
		i++;
	buffer.buffer_read = i;
	if (buffer.buffer_read == buffer.byte_read)
	{
		buffer.buffer_read = 0;
		if (buffer.buffer[i - 1] != '\n')
			s = read_recursive(s, fd, &buffer);
	}
	return (s);
}
