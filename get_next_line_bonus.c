/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezakyure <ezakyure@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/21 05:56:26 by ezakyure          #+#    #+#             */
/*   Updated: 2026/08/21 05:56:26 by ezakyure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*read_line(int fd, char *stack)
{
	char	*buffer;
	int		read_byte;

	read_byte = 1;
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	while (!ft_strchr(stack, '\n') && read_byte != 0)
	{
		read_byte = read(fd, buffer, BUFFER_SIZE);
		if (read_byte == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[read_byte] = '\0';
		stack = ft_strjoin(stack, buffer);
	}
	free(buffer);
	return (stack);
}

char	*new_line(char *str)
{
	int		i;
	int		s;
	char	*rest;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i] != '\n' && str[i])
		i++;
	if (str[i] == '\0')
	{
		free(str);
		return (NULL);
	}
	rest = malloc(sizeof(char) * (ft_strlen(str) - i + 1));
	if (!rest)
		return (NULL);
	i++;
	s = 0;
	while (str[i])
		rest[s++] = str[i++];
	rest[s] = '\0';
	free(str);
	return (rest);
}

char	*gett_line(char *stack)
{
	char	*ret;
	int		after_newline;
	int		i;

	if (!stack || stack[0] == '\0')
		return (NULL);
	i = 0;
	after_newline = newline_counter(stack);
	ret = malloc(sizeof(char) * (after_newline + 1));
	if (!ret)
		return (NULL);
	while (stack[i] != '\0' && stack[i] != '\n')
	{
		ret[i] = stack[i];
		i++;
	}
	if (stack[i] == '\n')
	{
		ret[i] = stack[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

t_gnl	*get_node(t_gnl **lst, int fd)
{
	t_gnl	*cur;
	t_gnl	*node;

	cur = *lst;
	while (cur)
	{
		if (cur->fd == fd)
			return (cur);
		cur = cur->next;
	}
	node = malloc(sizeof(t_gnl));
	if (!node)
		return (NULL);
	node->fd = fd;
	node->stack = NULL;
	node->next = *lst;
	*lst = node;
	return (node);
}

char	*get_next_line(int fd)
{
	static t_gnl	*lst;
	t_gnl			*node;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	node = get_node(&lst, fd);
	if (!node)
		return (NULL);
	node->stack = read_line(fd, node->stack);
	if (!node->stack)
	{
		free_node(&lst, fd);
		return (NULL);
	}
	line = gett_line(node->stack);
	node->stack = new_line(node->stack);
	if (!node->stack)
		free_node(&lst, fd);
	return (line);
}
