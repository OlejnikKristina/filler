/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   surround_game.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: krioliin <krioliin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/28 17:49:50 by krioliin       #+#    #+#                */
/*   Updated: 2019/08/02 15:19:09 by krioliin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

void	last_enemy_activity(t_map *map, int target[2])
{
	int		y;
	int		x;

	y = 0;
	x = 0;
	while (y < map->max_y)
	{
		while (x < map->max_x + 4)
		{
			if (map->map[y][x] == map->enemy &&
				(map->map[y][x] != map->old_map[y][x]))
			{
				target[0] = x;
				target[1] = y;
				return ;
			}
			x++;
		}
		x = 0;
		y++;
	}
//	target[0] = 4242;
//	target[1] = 4242;
}

bool	block_enemy(t_game *game, t_map *map, int *y, int *x, bool reset)
{
	int			target[2];
	int static	ex_x;
	int static	ex_y;
	int static	manh_dst;

	if (reset == 0)
		reset_values(&ex_x, &ex_y, &manh_dst);
	if (game->stop_checking)
	{
		*x = ex_x;
		*y = ex_y;
		ft_dprintf(fd_test, "FINAL y %d x %d ",
		*y - y_cut_top, *x - x_cut_left - 4);
		reset_values(&ex_x, &ex_y, &manh_dst);
		return (false);
	}
	if (!map->old_map)
		return (true);
	last_enemy_activity(map, target);
	if (manheten_dist(target[0], target[1], *x, *y) <= manh_dst)
	{
		ex_x = *x;
		ex_y = *y;
		manh_dst = manheten_dist(target[0], target[1], *x, *y);
	}
	ft_dprintf(fd_test, "Coord y %d x %d ",
	*y - y_cut_top, *x - x_cut_left - 4);

	ft_dprintf(fd_test, "lea y %d x %d  manht dist %d\n",
	target[1], target[0], manh_dst);
	return (false);
}

bool	b(t_game *game, t_map *map, int *y, int *x)
{
	bool return_value;
	return_value =  block_enemy(game, map, x, y, game->reset);
	game->reset = (game->stop_checking) ? 0 : 1;
	return (false);
}
