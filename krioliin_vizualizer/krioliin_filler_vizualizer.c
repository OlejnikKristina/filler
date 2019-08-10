/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   krioliin_filler_vizualizer.c                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: krioliin <krioliin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/28 17:49:50 by krioliin       #+#    #+#                */
/*   Updated: 2019/08/09 23:20:01 by krioliin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <errno.h>

size_t		ft_strlen(const char *s1)
{
	size_t i;

	i = 0;
	while (s1[i] != '\0')
		i++;
	return (i);
}

void	ft_putstr(char const *str)
{
	if (!str)
		return ;
	write(1, str, ft_strlen(str));
}

void	ft_bzero(void *s, size_t n)
{
	while (n > 0)
	{
		*((unsigned char *)s) = '\0';
		n--;
		s++;
	}
}

void	ft_char_replace(char *str, char from, char to)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == from)
			str[i] = to;
		i++;
	}
}

int		main(int argc, char **argv)
{
	int		dest_fd;
	int		src_fd;
	char	line[1001];
	int		i;

	errno = 0;
	if (src_fd == -1)
		src_fd = 0;
	if (argc == 2)
		src_fd = open(argv[1], O_RDONLY);
	else
		src_fd = open("test.txt", O_RDONLY);
	dest_fd = open("map.txt", O_WRONLY|O_TRUNC|O_CREAT, S_IREAD|S_IWRITE);
	ft_bzero(line, 1001);
	// if (errno)
	// {
	// 	perror("Error can't read file");
	// 	return (0);
	// }
	while (read(src_fd, line, 1000))
	{
		line[1000] = '\0';
		ft_char_replace(line, '<', 'a');
		write(dest_fd, line, ft_strlen(line));
		ft_bzero(line, 1001);
	}
	return (0);
}