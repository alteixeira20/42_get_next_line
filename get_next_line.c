/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paalexan <paalexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 15:20:08 by paalexan          #+#    #+#             */
/*   Updated: 2025/01/09 17:37:06 by paalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen_gnl(const char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

static char	*handle_read_error(char *buffer, char *leftover)
{
	free(buffer);
	free(leftover);
	return (NULL);
}

static char	*read_to_buffer(int fd, char *leftover)
{
	char	*buffer;
	int		bytes_read;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (handle_read_error(buffer, leftover));
		buffer[bytes_read] = '\0';
		leftover = ft_strjoin_gnl(leftover, buffer);
		if (!leftover || ft_strchr_gnl(leftover, '\n'))
			break ;
	}
	free(buffer);
	return (leftover);
}

static char	*extract_line(char **leftover)
{
	char	*line;
	char	*tmp;
	char	*newline_pos;

	newline_pos = ft_strchr_gnl(*leftover, '\n');
	if (newline_pos)
	{
		line = ft_substr_gnl(*leftover, 0, newline_pos - *leftover + 1);
		tmp = ft_strdup_gnl(newline_pos + 1);
		if (!tmp)
		{
			free(line);
			return (NULL);
		}
		free(*leftover);
		*leftover = tmp;
	}
	else
	{
		line = ft_strdup_gnl(*leftover);
		free(*leftover);
		*leftover = NULL;
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*leftover;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	leftover = read_to_buffer(fd, leftover);
	if (!leftover || !*leftover)
	{
		free(leftover);
		leftover = NULL;
		return (NULL);
	}
	line = extract_line(&leftover);
	if (!line)
	{
		free(leftover);
		leftover = NULL;
	}
	return (line);
}
/*
#include <stdio.h>
int	main(void)
{
	int	fd;
	char	*line;

	// Open the file "test.txt" in read-only mode
	fd = open("test.txt", O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		return (1);
	}
	// Read lines using get_next_line and print them
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line); // Don't forget to free the line after use
	}
	// Close the file descriptor
	close(fd);
	return (0);
}*/
