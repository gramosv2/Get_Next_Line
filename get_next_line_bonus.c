/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goramos- <goramos-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 18:29:35 by goramos-          #+#    #+#             */
/*   Updated: 2025/11/08 09:37:39 by goramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_free(char *s1, char *s2)
{
	if (s1)
		free(s1);
	if (s2)
		free(s2);
	return (NULL);
}

static char	*ft_read_file(int fd, char *storage)
{
	char	*buffer;
	ssize_t	bytes_read;

	if (ft_strchr(storage, '\n'))
		return (storage);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (ft_free(storage, NULL));
	bytes_read = 1;
	while (!ft_strchr(storage, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (ft_free(storage, buffer));
		buffer[bytes_read] = '\0';
		storage = ft_strjoin(storage, buffer);
		if (!storage)
			return (ft_free(NULL, buffer));
	}
	free(buffer);
	return (storage);
}

static char	*ft_extract_line(char *buf)
{
	char	*line;
	size_t	i;

	if (!buf || !*buf)
		return (NULL);
	i = 0;
	while (buf[i] && buf[i] != '\n')
		i++;
	line = malloc(i + (buf[i] == '\n') + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (buf[i] && buf[i] != '\n')
	{
		line[i] = buf[i];
		i++;
	}
	if (buf[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

static char	*ft_new_buffer(char *buf)
{
	size_t	i;
	char	*new_buf;

	if (!buf)
		return (NULL);
	i = 0;
	while (buf[i] && buf[i] != '\n')
		i++;
	if (!buf[i])
		return (ft_free(buf, NULL));
	new_buf = ft_strdup_from(buf, i + 1);
	free(buf);
	if (!new_buf || !*new_buf)
	{
		free(new_buf);
		return (NULL);
	}
	return (new_buf);
}

char	*get_next_line(int fd)
{
	static char	*buffer[MAX_FD];
	char		*line;

	if (fd < 0 || fd >= MAX_FD || BUFFER_SIZE <= 0)
		return (NULL);
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer[fd] = ft_read_file(fd, buffer[fd]);
	if (!buffer[fd])
	{
		buffer[fd] = NULL;
		return (NULL);
	}
	line = ft_extract_line(buffer[fd]);
	if (!line)
	{
		free(buffer[fd]);
		buffer[fd] = NULL;
		return (NULL);
	}
	buffer[fd] = ft_new_buffer(buffer[fd]);
	return (line);
}

// char	*get_next_line(int fd)
// {
// 	static char	*buffer[MAX_FD];
// 	char		*line;

// 	if (fd < 0 || fd >= MAX_FD || BUFFER_SIZE <= 0)
// 		return (NULL);
// 	buffer[fd] = ft_read_file(fd, buffer[fd]);
// 	if (!buffer[fd])
// 		return (NULL);
// 	line = ft_return_line(buffer[fd]);
// 	buffer[fd] = ft_remove_line(buffer[fd]);
// 	return (line);
// }
