/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   attack_top.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: krioliin <krioliin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/08/04 10:15:00 by krioliin       #+#    #+#                */
/*   Updated: 2019/08/11 22:08:19 by krioliin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

int		target_top_x(t_map *map, char enemy_chr)
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
	int static		pre_x;
	int static		pre_y;
	int static		manhdst;

	if (reset == 0)
		reset_values(&pre_x, &pre_y, &manhdst);
	if (game->stop_checking)
	{
		*yx[0] = pre_y;
		*yx[1] = pre_x;
		reset_values(&pre_x, &pre_y, &manhdst);
		if (ft_strchr(map->map[0], map->player) ||
			!ft_strchr(map->map[0], '.'))
		{
			game->hit_top = true;
			return (true);
		}
		return (false);
	}
	if (manheten_dist(target_top_x(map, map->enemy), 0, *yx[1], *yx[0]) <= manhdst)
	{
		pre_y = *yx[0];
		pre_x = *yx[1];
		manhdst = manheten_dist(target_top_x(map, map->enemy), 0, *yx[1], *yx[0]);
	}
	return (false);
}
