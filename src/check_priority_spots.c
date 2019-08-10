/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_priority_spots.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: krioliin <krioliin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/28 17:49:50 by krioliin       #+#    #+#                */
/*   Updated: 2019/08/10 18:31:30 by krioliin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

bool	is_enemy_close(t_map *map, short map_edge[2], short y, short x)
{
	short	local_x;
	short	local_y;

	local_x = x;
	local_y = y;
/* Check 10% of spots from right side*/
	while (local_x < map_edge[0] + map_edge[0] + 4)
	{
		if (map->map[y][local_x] == map->enemy)
			return (true);
		local_x++;
	}
	local_x = x;
/* Check 10% of spots from left side*/
	while (4 <= local_x)
	{
		if (map->map[y][local_x] == map->enemy)
			return (true);
		local_x--;
	}
/* Check 10% of spots from top*/
	while (0 <= local_y)
	{
		if (map->map[local_y][x] == map->enemy)
			return (true);
		local_y--;
	}
	local_y = y;
/* Check 10% of spots from bottom*/
	while (local_y < map_edge[1] + map_edge[1])
	{
		if (map->map[local_y][x] == map->enemy)
			return (true);
		local_y++;
	}
	return (false);
}


void	left_priority_spots(t_map *map, short map_edge[2],
		t_coord *priority_spots[500], short *num)
{
	short	y;
	short	x;

	y = 0;
	x = 4;
	while (y < map->max_y)
	{
		while (x < map_edge[0] + 4)
		{
			if (map->map[y][x] == map->player)
				if (is_enemy_close(map, map_edge, y, x))
				{
					priority_spots[*num]->x = x;
					priority_spots[*num]->y = y;
					*num += 1;
				}
			x++;
		}
		y++;
	}
}

bool	select_prior_spots(t_coord *spots[500], int y, int x)
{
	short	i;

	i = 0;
	while (i < 500)
	{
		if (spots[i]->x == x && spots[i]->y == y)
			return (true);
		i++;
	}
	return (false);
}

bool	find_prior_spt(t_map *map, t_figure *figure,
		t_game *game, t_coord *prior_spots[500])
{
	int		y;
	int		x;
	int		max_y_field;

	y = 0;
	x = 4;
	max_y_field = max_y_filed(map, figure->cut_fig + 1);
	y_cut_top = cut_y_top(figure);
	x_cut_left = cut_x_left(figure);
	while (y < max_y_field)
	{
		while (x < map->max_x + 4)
		{
			if (check_spot(figure->cut_fig, map, y, x, figure))
			{
				if (select_prior_spots(prior_spots, y, x))
				{
					ft_printf("%d %d\n", y - cut_y_top(figure),
					 x - cut_x_left(figure) - 4);
					ft_dprintf(fd_test, "spot 1(y %d; x %d)\n",
					y - cut_y_top(figure), x - cut_x_left(figure) - 4);
					//print_spot(figure->cut_fig, map, y, x, figure);
					return (true);
				}
			}
			x++;
		}
		x = 4;
		y++;
	}
	return (false);
}


/*
	map_edge[0] 10% from horizontal map size.;
	map_edge[1] 10% from vertical map size;
*/

bool	check_priority_spots(t_map *map, t_coord *priority_spots[500])
{
	short		map_edge[2];
	short		prior_spt_num;

	prior_spt_num = 0;
	map_edge[0] = (map->max_x * 10 / 100);
	map_edge[1] = (map->max_y * 10 / 100);
	left_priority_spots(map, map_edge, priority_spots, &prior_spt_num);
	return (prior_spt_num);
}
