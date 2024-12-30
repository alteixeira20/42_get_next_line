/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_multiple_fd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paalexan <paalexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 17:06:28 by paalexan          #+#    #+#             */
/*   Updated: 2024/12/30 17:17:12 by paalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../get_next_line_bonus.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int	main(void) {
	int	fd1 = open("tests/test_cases/42_with_nl", O_RDONLY);
	int	fd2 = open("tests/test_cases/43_with_nl", O_RDONLY);

	char	*line1 = get_next_line(fd1);
	char	*line2 = get_next_line(fd2);

	while (line1 || line2) {
		if (line1) {
			printf("FD1: %s", line1);
			free(line1);
		}
		if (line2) {
			printf("FD2: %s", line2);
			free(line2);
		}
		line1 = get_next_line(fd1);
		line2 = get_next_line(fd2);
	}

	close(fd1);
	close(fd2);
	return (0);
}

