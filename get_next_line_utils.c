/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezakyure <ezakyure@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/21 05:55:50 by ezakyure          #+#    #+#             */
/*   Updated: 2026/08/21 05:55:51 by ezakyure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(char *str)
{
	char	*s;

	s = str;
	while (*s)
		s++;
	return (s - str);
}

int	newline_counter(char *raw_str)
{
	char	*s;

	s = raw_str;
	while (*s && *s != '\n')
		s++;
	if (*s == '\n')
		s++;
	return (s - raw_str);
}

char	*ft_strjoin(char *left_str, char *buff)
{
	char	*str;
	char	*w;
	char	*r;
	int		l;

	if (!buff)
		return (NULL);
	l = 0;
	if (left_str)
		l = ft_strlen(left_str);
	str = malloc(sizeof(char) * (l + ft_strlen(buff) + 1));
	if (!str)
		return (NULL);
	w = str;
	r = left_str;
	while (r && *r)
		*w++ = *r++;
	r = buff;
	while (*r)
		*w++ = *r++;
	*w = '\0';
	if (left_str)
		free(left_str);
	return (str);
}

char	*ft_strchr(char *s, int c)
{
	if (!s)
		return (0);
	while (*s)
	{
		if (*s == (char)c)
			return (s);
		s++;
	}
	if ((char)c == '\0')
		return (s);
	return (0);
}
