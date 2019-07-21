/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: krioliin <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/16 18:12:34 by krioliin       #+#    #+#                */
/*   Updated: 2019/07/16 15:49:33 by krioliin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include "libft.h"
# include <stdlib.h>
# include <stddef.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# define BUFF_SIZE 1

typedef struct			s_fd_list
{
	int					fd;
	char				*tail;
	struct s_fd_list	*next;
}						t_fd_list;

typedef struct		s_line
{
    int				fd;
    char			*str;
    struct s_line	*next;
}					t_line;

int					get_next_line(int fd, char **line);

int						get_next_line(const int fd, char **line);

#endif
