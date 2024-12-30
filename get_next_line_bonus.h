/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paalexan <paalexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 14:44:58 by paalexan          #+#    #+#             */
/*   Updated: 2024/12/30 20:19:05 by paalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

size_t	ft_strlen_gnl(const char *str);
char	*ft_strchr_gnl(const char *s, int c);
void	ft_strcpy_gnl(char *dest, char *src, unsigned int *index);
char	*ft_strjoin_gnl(char *s1, char *s2);
char	*ft_strdup_gnl(const char *s);
char	*get_next_line(int fd);
char	*ft_substr_gnl(char const *s, unsigned int start, size_t len);

#endif
