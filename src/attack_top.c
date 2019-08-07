/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   attack_top.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: krioliin <krioliin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/08/04 10:15:00 by krioliin       #+#    #+#                */
/*   Updated: 2019/08/04 10:15:02 by krioliin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

int		target_top_x(t_map *map, char enemy_chr, bool enemy_from_right)
{
	short		x;
	short		y;
	short		my_topest_open_spot;

	y = 0;
	x = map->max_x;
	while (4 <= x)
	{
		while (y < map->max_y)
		{
			if (map->map[y][x] == map->player)
			{
				ft_dprintf(fd_test, "topest open right spot y%d x%d\n", y, x);
				return (x - 2);
			}
			if (map->map[y][x] == enemy_chr)
				break ;
			y++;
		}
		x--;
		y = 0;
	}
	return (x - 2);
}

bool	top(t_game *game, t_map *map, int *y, int *x, bool reset)
{
	int static		pre_x = 0;
	int static		pre_y = 0;
	int static		manhdst;

	if (reset == 0)
		reset_values(&pre_x, &pre_y, &manhdst);
	if (game->stop_checking)
	{
		*x = pre_x;
		*y = pre_y;
		reset_values(&pre_x, &pre_y, &manhdst);
		if (*y - game->fig_max_y <= 0)
		{
			game->hit_top = true;
			ft_dprintf(fd_test, "Hit target --> TOP\n");
			return (true);
		}
		ft_dprintf(fd_test, "Target --> TOP Final ManhDst: %d\n", manhdst);
		return (false);
	}
	if (manheten_dist(target_top_x(map, map->enemy, 1), 0, *x, *y) <= manhdst)
	{
		pre_x = *x;
		pre_y = *y;
		manhdst = manheten_dist(map->max_y, target_bottom(map, map->enemy), *x, *y);
	}
	return (false);
}
