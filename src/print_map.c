/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_map.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: krioliin <krioliin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/30 15:19:11 by krioliin       #+#    #+#                */
/*   Updated: 2019/07/20 20:56:03 by krioliin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

void	map_print(t_map *map)
{
	unsigned	y;
	unsigned	x;

	y = 0;
	printf("Map size y %d x %d\n", map->max_y, map->max_x);
	while (y < map->max_y)
	{
		x = 0;
		while (x < map->max_x + 4)
		{
			if (map->map[y][x] == 'O')
				printf("\033[1;33m%c\033[0;0m", map->map[y][x]);
			else if (map->map[y][x] == 'X')
				printf("\033[1;36m%c\033[0;0m", map->map[y][x]);
			else if (map->map[y][x] == '.')
				printf("\033[1;35m%c\033[0;0m", map->map[y][x]);
			else
				printf("\033[1;34m%c\033[0;0m", map->map[y][x]);
			x++;
		}
		printf(" \n");
		y++;
	}
}
