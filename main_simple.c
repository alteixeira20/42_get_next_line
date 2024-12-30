/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paalexan <paalexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 21:16:13 by paalexan          #+#    #+#             */
/*   Updated: 2024/12/30 21:17:04 by paalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h" // Include your header file

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
}
