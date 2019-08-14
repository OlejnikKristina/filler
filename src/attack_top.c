/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   attack_top.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: krioliin <krioliin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/08/04 10:15:00 by krioliin       #+#    #+#                */
/*   Updated: 2019/08/14 14:15:33 by krioliin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int		target_top(t_map *map, char enemy_chr)
{
	short		x;
	short		y;

	y = 0;
	x = map->max_x;
	while (4 <= x)
	{
		while (y < map->max_y)
		{
			if (map->map[y][x] == map->player)
				return (x - 2);
			if (map->map[y][x] == enemy_chr)
				break ;
			y++;
		}
		x--;
		y = 0;
	}
	return (x - 2);
}

bool	top(t_game *game, t_map *map, int **yx, bool reset)
{
	static int		pre_x;
	static int		pre_y;
	static int		manhdst;

	if (reset == 0)
		reset_values(&pre_x, &pre_y, &manhdst);
	if (game->stop_checking)
	{
		*yx[0] = pre_y;
		*yx[1] = pre_x;
		reset_values(&pre_x, &pre_y, &manhdst);
		if (ft_strchr(map->map[0], map->player) || !ft_strchr(map->map[0], '.'))
			return (ret_set(&game->hit_right));
		return (false);
	}
	if (manhtn_dist(target_top(map, map->enemy), 0, *yx[1], *yx[0]) <= manhdst)
	{
		pre_y = *yx[0];
		pre_x = *yx[1];
		manhdst = manhtn_dist(target_top(map, map->enemy), 0, *yx[1], *yx[0]);
	}
	return (false);
}
