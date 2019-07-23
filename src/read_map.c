/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_map.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: krioliin <krioliin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/30 15:19:11 by krioliin       #+#    #+#                */
/*   Updated: 2019/07/23 18:09:45 by krioliin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

void		map_del(t_map *map)
{
	int		y;

	y = 0;
	if (!map)
		return ;
	while (y < map->max_y)
	{
		if (map->map[y])
			ft_strdel(&map->map[y]);
		y++;
	}
	ft_strdel(map->map);
	map = NULL;
}

static	void	map_parse(t_map *map)
{
	unsigned	y;
	char		*line;

	y = 0;
	map->map = (char **)malloc(sizeof(char *) * map->max_y + 5);
	ft_dprintf(fd_test, "***** MAP ******\n");
	ft_dprintf(fd_test, "    0123456789012345678901234567890123456789\n");
	while (y < map->max_y)
	{
		get_next_line(STDIN_FILENO, &line);
		map->map[y] = ft_strdup(line);
		map->map[y] = ft_superjoin(&map->map[y], "||||||||||");
		ft_dprintf(fd_test, "%s\n", map->map[y]);
		ft_strdel(&line);
		y++;
	}
	ft_dprintf(fd_test, "    0123456789012345678901234567890123456789\n");
	while (y < map->max_y + 4)
	{
		map->map[y] = ft_strnew(map->max_x + 15);
		ft_memset((void *)map->map[y], '-', map->max_x + 14);
		ft_dprintf(fd_test, "%s\n", map->map[y]);
		y++;
	}
}

bool	skeep_lines()
{
	char		*line;

	if (get_next_line(0, &line) <= 0)
		return (false);
	if (ft_strstr(line, "Plateau"))
	{
		ft_strdel(&line);
		get_next_line(STDIN_FILENO, &line);
	}
	ft_strdel(&line);
	return (true);
}

bool		read_map(t_map *map)
{
	if (skeep_lines() == false)
		return (false);
	map_parse(map);
	(PRINT) ? map_print(map) : 1;
	return (true);
}
