/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_basic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paalexan <paalexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 17:05:33 by paalexan          #+#    #+#             */
/*   Updated: 2024/12/30 17:08:30 by paalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int	main(int argc, char **argv) {
	if (argc != 2) {
		printf("Usage: %s <test_file>\n", argv[0]);
		return (1);
	}

	int	fd = open(argv[1], O_RDONLY);
	if (fd < 0) {
		perror("Error opening file");
		return (1);
	}

	char	*line;
	while ((line = get_next_line(fd)) != NULL) {
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}
