/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paalexan <paalexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 15:20:08 by paalexan          #+#    #+#             */
/*   Updated: 2024/12/20 17:11:31 by paalexan         ###   ########.fr       */
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
	static char	*leftover;
	char	*line;
	char	*tmp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	leftover = read_to_buffer(fd, leftover);
	if (!leftover || !*leftover)
	{
		free(leftover);
		return (NULL);
	}
	if (ft_strchr_gnl(leftover, '\n'))
	{
		line = ft_substr_gnl(leftover, 0, ft_strchr_gnl(leftover, '\n') - leftover + 1);
		tmp = ft_strdup_gnl(ft_strchr_gnl(leftover, '\n') + 1);
		free(leftover);
		leftover = tmp;
	}
	else
	{
		line = ft_strdup_gnl(leftover);
		free(leftover);
		leftover = NULL;
	}
	return (line);
}
