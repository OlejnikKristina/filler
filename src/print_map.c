/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_map.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: krioliin <krioliin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/30 15:19:11 by krioliin       #+#    #+#                */
/*   Updated: 2019/08/02 13:31:55 by krioliin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"
/*
bool	right_wall(t_enemy *enemy, t_map *map, int *y, int *x, bool reset)
{
	int static		pre_x;
	int static		pre_y;
	int static		manhdst;

	ft_dprintf(fd_test, "Coord to check y%d x%d mnht %d\n",
	*y - y_cut_top, *x - x_cut_left - 4, manhdst);
	if (reset == 0)
	{
		ft_dprintf(fd_test, "First coordinat bottom\n");
		pre_x = 0;
		pre_y = 0;
		manhdst = 1000;
		reset = 1;
	}
	if (enemy->stop_checking)
	{
		*x = pre_x;
		*y = pre_y;
		pre_x = 0;
		pre_y = 0;
		manhdst = 1000;
		if (map->max_x + 4 <= *x + enemy->fig_max_x)
		{
			enemy->hit_right = true;
			ft_dprintf(fd_test, "Hit target --> RIGHT WALL %d\n", enemy->fig_max_x);
			return (true);
		}
		ft_dprintf(fd_test, "Target --> RIGHT WALL\n");
	}
	if (*y == 0 && *x == 4)
	{
		pre_x = 0;
		pre_y = 0;
		ft_dprintf(fd_test, "First coordinat right\n");
	}
	if (pre_x == 0 && pre_y == 0)
		manhdst = 1000;
	//	manhdst = mnhtn_rw(map->max_x, target_rw(map, map->enemy), *x, *y);
	if (mnhtn_rw(map->max_x, target_rw(map, map->enemy), *x, *y) <= manhdst)
	{
		pre_x = *x;
		pre_y = *y;
		manhdst = mnhtn_rw(map->max_x, target_rw(map, map->enemy), *x, *y);
		return (true);
	}
	return (false);
}

bool	bottom(t_enemy *enemy, t_map *map, int *y, int *x,
int *temp_x, int *temp_y, bool reset)
{
	int static		pre_x;
	int static		pre_y;
	int static		manhdst;

	if (reset == 0)
	{
		ft_dprintf(fd_test, "First coordinat bottom\n");
		pre_x = 0;
		pre_y = 0;
		manhdst = 1000;
		reset = 1;
	}
	if (enemy->stop_checking)
	{
		*x = pre_x;
		*y = pre_y;
		pre_x = 0;
		pre_y = 0;
		manhdst = 1000;
		if (map->max_y <= enemy->fig_max_y + *y)
		{
			enemy->hit_bottom = true;
			ft_dprintf(fd_test, "Hit target --> BOTTOM\n");
			return (true);
		}
		enemy->stop_checking = false;
		ft_dprintf(fd_test, "Target --> BOTTOM Final ManhDst: %d\n", manhdst);
	}
	if (mnhtn_rw(map->max_y, target_bottom(map, map->enemy), *x, *y) <= manhdst)
	{
		pre_x = *x;
		pre_y = *y;
		*temp_x = *x;
		*temp_y = *y;
		manhdst = mnhtn_rw(map->max_y, target_bottom(map, map->enemy), *x, *y);
		return (true);
	}
	return (false);
} */
void	map_print(t_map *map)
{
	unsigned	y;
	unsigned	x;

	y = 1;
	printf("Map size y %d x %d\n", map->max_y, map->max_x);
	printf("\033[1;34m    0123456789012345678901234567890123456789\033[0;0m\n");
	while (y < map->max_y)
	{
		x = 0;
		while (x < map->max_x + 14)
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
