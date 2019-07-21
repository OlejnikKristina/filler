/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_map.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: krioliin <krioliin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/30 15:19:11 by krioliin       #+#    #+#                */
/*   Updated: 2019/07/20 20:58:05 by krioliin      ########   odam.nl         */
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
	map->map = (char **)malloc(sizeof(char *) * map->max_y);
	ft_dprintf(fd_test, "***** MAP ******\n");
	while (y < map->max_y)
	{
		get_next_line(STDIN_FILENO, &line);
		map->map[y] = ft_strdup(line);
		ft_dprintf(fd_test, "%s\n", line);
		ft_strdel(&line);
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
