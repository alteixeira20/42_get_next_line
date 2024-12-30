/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_edge_cases_m.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paalexan <paalexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 17:06:01 by paalexan          #+#    #+#             */
/*   Updated: 2024/12/30 17:12:51 by paalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int	main(void) {
	// Test invalid FD
	char	*line = get_next_line(-1);
	if (line == NULL)
		printf("Invalid FD test passed\n");
	else
		printf("Invalid FD test failed\n");

	// Test empty file
	int	fd = open("tests/test_cases/empty", O_RDONLY);
	line = get_next_line(fd);
	if (line == NULL)
		printf("Empty file test passed\n");
	else
		printf("Empty file test failed\n");
	free(line);
	close(fd);

	return (0);
}

