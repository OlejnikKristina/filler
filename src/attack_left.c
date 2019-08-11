/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   attack_left.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: krioliin <krioliin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/08/04 10:14:27 by krioliin       #+#    #+#                */
/*   Updated: 2019/08/11 22:06:37 by krioliin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

bool	left_wall_hit(t_map *map)
{
	int		i;

	i = 0;
	while (i < map->max_y)
	{
		if (map->map[i][4] == map->player)
			return (true);
		i++;
	}
	return (false);
}

bool	left_wall(t_game *game, t_map *map, int **yx, bool reset)
{
	int static		pre_x;
	int static		pre_y;
	int static		manh_dst;

	(reset == 0) ? reset_values(&pre_x, &pre_y, &manh_dst) : 1;
	if (game->stop_checking)
	{
		*yx[0] = pre_y;
		*yx[1] = pre_x;
		reset_values(&pre_x, &pre_y, &manh_dst);
		if (left_wall_hit(map))
		{
			game->hit_left = true;
			return (true);
		}
		return (false);
	}
	if (manheten_dist(4, target_rw(map, game, map->enemy), *yx[1], *yx[0]) <= manh_dst)
	{
		pre_y = *yx[0];
		pre_x = *yx[1];
		manh_dst = manheten_dist(map->max_x, target_rw(map, game, map->enemy), *yx[1], *yx[0]);
	}
	return (false);
}
