/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   attack_right.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: krioliin <krioliin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/08/04 10:14:35 by krioliin       #+#    #+#                */
/*   Updated: 2019/08/14 14:15:08 by krioliin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int				target_rw_second_part(t_map *map,
				char enemy_chr)
{
	int		y;

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
	return (target_rw_second_part(map, enemy_chr));
}

bool			right_wall(t_game *game, t_map *map, int **yx, bool reset)
{
	static int		pre_x;
	static int		pre_y;
	static int		manh_dst;

	(reset == 0) ? reset_values(&pre_x, &pre_y, &manh_dst) : 1;
	if (game->stop_checking)
	{
		*yx[0] = pre_y;
		*yx[1] = pre_x;
		reset_values(&pre_x, &pre_y, &manh_dst);
		if ((map->max_x <= game->fig_max_x + *yx[1]))
			return (ret_set(&game->hit_right));
		return (false);
	}
	if (manhtn_dist(map->max_x,
		target_rw(map, game, map->enemy), *yx[1], *yx[0]) <= manh_dst)
	{
		pre_y = *yx[0];
		pre_x = *yx[1];
		manh_dst = manhtn_dist(map->max_x,
		target_rw(map, game, map->enemy), *yx[1], *yx[0]);
	}
	return (false);
}
