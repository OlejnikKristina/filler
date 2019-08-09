/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   attack_bottom.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: krioliin <krioliin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/08/04 10:14:52 by krioliin       #+#    #+#                */
/*   Updated: 2019/08/09 17:41:02 by krioliin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

int		target_bottom(t_map *map, char game_chr)
{
	int		x;
	int		y;
	bool	game_right;

	y = 0;
	x = 4;
	while (x < map->max_x + 4)
	{
		while (y < map->max_y)
		{
			if (map->map[y][x] == game_chr)
			{
				(x != 0) ? x-- : 1;
				(x != 0) ? x-- : 1;
				return (x);
			}
			y++;
		}
		y = 0;
		x++;
	}
	return (x);
}

bool	bottom(t_game *game, t_map *map, int *y, int *x, bool reset)
{
	int static		pre_x;
	int static		pre_y;
	int static		manh_dst;

	if (reset == 0)
		reset_values(&pre_x, &pre_y, &manh_dst);
	if (game->stop_checking)
	{
		*x = pre_x;
		*y = pre_y;
		reset_values(&pre_x, &pre_y, &manh_dst);
		if (map->max_y <= game->fig_max_y + *y)
		{
			game->hit_bottom = true;
			ft_dprintf(fd_test, "Hit target --> BOTTOM\n");
			return (true);
		}
		ft_dprintf(fd_test, "Target --> BOTTOM\n");
		return (false);
	}
	if (manheten_dist(map->max_y, target_bottom(map, map->enemy), *x, *y) <= manh_dst)
	{
		pre_x = *x;
		pre_y = *y;
		manh_dst = manheten_dist(map->max_y, target_bottom(map, map->enemy), *x, *y);
	}
	return (false);
}