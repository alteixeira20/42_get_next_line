/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paalexan <paalexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 15:20:08 by paalexan          #+#    #+#             */
/*   Updated: 2024/12/20 17:32:02 by paalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_to_buffer(int fd, char *leftover)
{
	char	*buffer;
	int	bytes_read;
	
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(buffer);
			free(leftover);
			return (NULL);
		}
		if (bytes_read == 0)
			break;
		buffer[bytes_read] = '\0';
		leftover = ft_strjoin_gnl(leftover, buffer);
		if (!leftover)
		{
			free(buffer);
			return (NULL);
		}
		if (ft_strchr_gnl(leftover, '\n'))
			break;
	}
	free(buffer);
	return (leftover);
}

char	*get_next_line(int fd)
{
	static char	*leftover[FD_SETSIZE];
	char	*line;
	char	*tmp;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= FD_SETSIZE)
		return (NULL);
	leftover[fd] = read_to_buffer(fd, leftover[fd]);
	if (!leftover[fd] || !*leftover[fd])
	{
		free(leftover[fd]);
		leftover[fd] = NULL;
		return (NULL);
	}
	if (ft_strchr_gnl(leftover[fd], '\n'))
	{
		line = ft_substr_gnl(leftover[fd], 0, ft_strchr_gnl(leftover[fd], '\n') - leftover[fd] + 1);
		tmp = ft_strdup_gnl(ft_strchr_gnl(leftover[fd], '\n') + 1);
		free(leftover[fd]);
		leftover[fd] = tmp;
	}
	else
	{
		line = ft_strdup_gnl(leftover[fd]);
		free(leftover[fd]);
		leftover[fd] = NULL;
	}
	return (line);
}
