/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goramos- <goramos-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 18:29:35 by goramos-          #+#    #+#             */
/*   Updated: 2025/11/07 18:36:48 by goramos-         ###   ########.fr       */
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
char	*ft_read_file(int fd, char *s1)
{
	char	*buffer;
	int		bytes_read;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (!ft_strchr(s1, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buffer);
			free(s1);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		s1 = ft_strjoin(s1, buffer);
		if (!s1)
			break ;
	}
	free(buffer);
	return (s1);
}

char	*ft_remove_line(char *buffer)
{
	int		z;
	int		s;
	char	*new_buffer;

	z = 0;
	while (buffer[z] && buffer[z] != '\n')
		z++;
	if (!buffer[z])
	{
		free(buffer);
		return (NULL);
	}
	new_buffer = malloc(sizeof(char) * (ft_strlen(buffer) - z));
	if (!new_buffer)
		return (NULL);
	z++;
	s = 0;
	while (buffer[z])
		new_buffer[s++] = buffer[z++];
	new_buffer[s] = '\0';
	free(buffer);
	return (new_buffer);
}

char	*ft_return_line(char *buffer)
{
	char	*line;
	int		z;

	z = 0;
	if (!buffer[z])
		return (NULL);
	while (buffer[z] && buffer[z] != '\n')
		z++;
	line = malloc(sizeof(char) * (z + 2));
	if (!line)
		return (NULL);
	z = 0;
	while (buffer[z] && buffer[z] != '\n')
	{
		line[z] = buffer[z];
		z++;
	}
	if (buffer[z] == '\n')
		line[z++] = '\n';
	line[z] = '\0';
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*buffer[MAX_FD];
	char		*line;

	if (fd < 0 || fd >= MAX_FD || BUFFER_SIZE <= 0)
		return (NULL);
	buffer[fd] = ft_read_file(fd, buffer[fd]);
	if (!buffer[fd])
		return (NULL);
	line = ft_return_line(buffer[fd]);
	buffer[fd] = ft_remove_line(buffer[fd]);
	return (line);
}
