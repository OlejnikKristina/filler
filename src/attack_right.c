/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   attack_right.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: krioliin <krioliin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/08/04 10:14:35 by krioliin       #+#    #+#                */
/*   Updated: 2019/08/11 23:49:21 by krioliin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

int				target_rw(t_map *map, t_game *game, char enemy_chr)
{
	int		y;

	if (game->hit_top == true)
	{
		y = map->max_y - 1;
		while (0 <= y)
		{
			if (ft_strchr(map->map[y], enemy_chr))
			{
				(y != 0) ? y++ : 1;
				(y != 0) ? y++ : 1;
				return (y);
			}
			y--;
		}
	}
	y = 0;
	while (y < map->max_y)
	{
		if (ft_strchr(map->map[y], enemy_chr))
		{
			(y != 0) ? y-- : 1;
			(y != 0) ? y-- : 1;
			return (y);
		}
		y++;
	}
	return (y);
}

bool			right_wall(t_game *game, t_map *map, int **yx, bool reset)
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
		if ((map->max_x <= game->fig_max_x + *yx[1]))
		{
			game->hit_right = true;
			return (true);
		}
		return (false);
	}
	if (manheten_dist(map->max_x, target_rw(map, game, map->enemy), *yx[1], *yx[0]) <= manh_dst)
	{
		pre_y = *yx[0];
		pre_x = *yx[1];
		manh_dst = manheten_dist(map->max_x, target_rw(map, game, map->enemy), *yx[1], *yx[0]);
	}
	return (false);
}