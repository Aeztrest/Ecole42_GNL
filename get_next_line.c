/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezakyure <ezakyure@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/21 05:55:42 by ezakyure          #+#    #+#             */
/*   Updated: 2026/08/21 05:55:43 by ezakyure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_line(int fd, char *stack)
{
	char	*buffer;
	int		read_byte;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (free(stack), NULL);
	read_byte = 1;
	while (!ft_strchr(stack, '\n') && read_byte > 0)
	{
		read_byte = read(fd, buffer, BUFFER_SIZE);
		if (read_byte < 0)
		{
			free(buffer);
			return (free(stack), NULL);
		}
		buffer[read_byte] = '\0';
		stack = ft_strjoin(stack, buffer);
		if (!stack)
			return (free(buffer), NULL);
	}
	free(buffer);
	return (stack);
}

char	*new_line(char *str)
{
	char	*nl;
	char	*rest;
	char	*w;

	if (!str)
		return (NULL);
	nl = ft_strchr(str, '\n');
	if (!nl)
		return (free(str), NULL);
	nl++;
	rest = malloc(sizeof(char) * (ft_strlen(nl) + 1));
	if (!rest)
		return (free(str), NULL);
	w = rest;
	while (*nl)
		*w++ = *nl++;
	*w = '\0';
	free(str);
	return (rest);
}

char	*gett_line(char *stack)
{
	char	*ret;
	char	*w;
	int		len;

	if (!stack || !*stack)
		return (NULL);
	len = newline_counter(stack);
	ret = malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (NULL);
	w = ret;
	while (len--)
		*w++ = *stack++;
	*w = '\0';
	return (ret);
}

char	*get_next_line(int fd)
{
	static char	*stack;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stack = read_line(fd, stack);
	if (!stack)
		return (NULL);
	line = gett_line(stack);
	stack = new_line(stack);
	return (line);
}
