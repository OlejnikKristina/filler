/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   attack_bottom.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: krioliin <krioliin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/08/04 10:14:52 by krioliin       #+#    #+#                */
/*   Updated: 2019/08/11 22:07:21 by krioliin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

int		target_bottom(t_map *map, char game_chr)
{
	int		x;
	int		y;

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

bool	bottom(t_game *game, t_map *map, int **yx, bool reset)
{
	int static		pre_x;
	int static		pre_y;
	int static		manh_dst;

	if (reset == 0)
		reset_values(&pre_x, &pre_y, &manh_dst);
	if (game->stop_checking)
	{
		*yx[0] = pre_y;
		*yx[1] = pre_x;
		reset_values(&pre_x, &pre_y, &manh_dst);
		if (ft_strchr(map->map[map->max_y - 1], map->player))
		{
			game->hit_bottom = true;
			return (true);
		}
		return (false);
	}
	if (manheten_dist(map->max_y, target_bottom(map, map->enemy), *yx[1], *yx[0]) <= manh_dst)
	{
		pre_y = *yx[0];
		pre_x = *yx[1];
		manh_dst = manheten_dist(map->max_y, target_bottom(map, map->enemy), *yx[1], *yx[0]);
	}
	return (false);
}