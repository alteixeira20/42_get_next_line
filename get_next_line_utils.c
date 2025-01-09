/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paalexan <paalexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 14:04:20 by paalexan          #+#    #+#             */
/*   Updated: 2025/01/09 16:49:37 by paalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_strchr_gnl(const char *s, int c)
{
	int	i;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
			return ((char *)(s + i));
		i++;
	}
	if ((unsigned char)c == '\0')
		return ((char *)(s + i));
	else
		return (NULL);
}

void	ft_strcpy_gnl(char *dest, char *src, unsigned int *index)
{
	unsigned int	i;

	i = 0;
	while (src[i])
	{
		dest[*index + i] = src[i];
		i++;
	}
	*index += i;
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char			*dest;
	unsigned int	len;
	unsigned int	index;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup_gnl(s2));
	if (!s2)
		return (ft_strdup_gnl(s1));
	len = ft_strlen_gnl(s1) + ft_strlen_gnl(s2) + 1;
	dest = malloc(len * sizeof(char));
	if (!dest)
		return (NULL);
	index = 0;
	ft_strcpy_gnl(dest, s1, &index);
	ft_strcpy_gnl(dest, s2, &index);
	dest[index] = '\0';
	free(s1);
	return (dest);
}

char	*ft_strdup_gnl(const char *s)
{
	size_t		len_s;
	char		*dest;
	int			i;

	if (!s)
		return (NULL);
	len_s = ft_strlen_gnl(s) + 1;
	dest = (char *)malloc(sizeof(char) * len_s + 1);
	if (!dest)
		return (NULL);
	i = 0;
	while (s[i])
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_substr_gnl(char const *s, unsigned int start, size_t len)
{
	char			*tmp;
	unsigned int	i;
	size_t			len_substr;

	if (!s)
		return (NULL);
	if (start >= ft_strlen_gnl(s))
		return (ft_strdup_gnl(""));
	len_substr = ft_strlen_gnl(s + start);
	if (len_substr < len)
		len = len_substr;
	tmp = (char *)malloc((len + 1) * sizeof(char));
	if (!tmp)
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		tmp[i] = s[start + i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}
