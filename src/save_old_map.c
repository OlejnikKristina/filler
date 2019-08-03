/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   save_old_map.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: krioliin <krioliin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/28 17:49:50 by krioliin       #+#    #+#                */
/*   Updated: 2019/08/03 21:32:29 by krioliin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

void	map_print_copy(t_map *map)
{
	unsigned	y;
	unsigned	x;

	y = 1;
	printf("Map size y %d x %d\n", map->max_y, map->max_x);
	printf("\033[1;34m    0123456789012345678901234567890123456789\033[0;0m\n");
	while (y < map->max_y)
	{
		printf("cpy %s\n", map->old_map[y]);
		y++;
	}
}


static void	rewrite_map(char ***map_dest, char **map_src, char num_rows)
{
	int		row;
	int		column;

	row = 0;
	column = 0;
	while (row < num_rows)
	{
		while (map_src[row][column])
		{
			(*map_dest)[row][column] = map_src[row][column];
			column++;
		}
		column = 0;
		row++;
	}
}

static void	copy_map(char ***map_dest, char **map_src, char num_rows)
{
	int		row;

	row = 0;
	*map_dest = (char **)ft_memalloc(sizeof(char *) * num_rows + 1);
	while (row < num_rows)
	{
		(*map_dest)[row] = ft_strdup(map_src[row]);
		row++;
	}
	(*map_dest)[row] = NULL;
}

void		save_old_map(t_map *map)
{
	if (map->old_map == NULL)
		copy_map(&map->old_map, map->map, map->max_y);
	else
		rewrite_map(&map->old_map, map->map, map->max_y);
//	map_print_copy(map);
}
