/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezakyure <ezakyure@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/21 05:56:14 by ezakyure          #+#    #+#             */
/*   Updated: 2026/08/21 06:00:02 by ezakyure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_gnl
{
	int				fd;
	char			*stack;
	struct s_gnl	*next;
}					t_gnl;

int					ft_strlen(char *str);
int					newline_counter(char *raw_str);
char				*ft_strjoin(char *left_str, char *buff);
char				*ft_strchr(char *str, int c);
void				free_node(t_gnl **lst, int fd);
t_gnl				*get_node(t_gnl **lst, int fd);
char				*get_next_line(int fd);
char				*gett_line(char *stack);
char				*new_line(char *str);
char				*read_line(int fd, char *stack);
#endif
