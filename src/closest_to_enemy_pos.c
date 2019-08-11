/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   closest_to_enemy_pos.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: krioliin <krioliin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/28 17:49:50 by krioliin       #+#    #+#                */
/*   Updated: 2019/08/11 20:51:32 by krioliin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

static bool	closest_enemy_spot(t_map *map, int coord[2], 
			int best_coord[2], int *best_manht_dst)
{
	int			manh_dst;
	int			i;
	int			j;

	j = 0;
	i = 4;
	manh_dst = 1000;
	while (j < map->max_y)
	{
		while (i < map->max_x + 4)
		{
			if (map->map[j][i] == map->enemy)
			{
				if (manheten_dist(i, j, coord[1], coord[0]) <= manh_dst)
					manh_dst = manheten_dist(i, j, coord[1], coord[0]);
			}
			i++;
		}
		i = 4;
		j++;
	}
	if (manh_dst <= *best_manht_dst)
	{
		best_coord[0] = coord[0];
		best_coord[1]= coord[1];
		*best_manht_dst = manh_dst;
	}
	return ((*best_manht_dst == 0) ? 1 : 0);
}

/*
**	best_coord[0] = y;
**	best_coord[1] = x;
**	Finding the closet position of enemy acording
**	to my current coordinats
*/

bool		closest_to_enemy_pos(t_game *game, t_map *map, int *y, int *x)
{
	int static	best_coord[2];
	int			coord[2];
	int static	best_manh_dst;

	if (game->stop_checking)
	{
		*y = best_coord[0];
		*x = best_coord[1];
		reset_values(&best_coord[1], &best_coord[0], &best_manh_dst);
	}
	if (best_manh_dst == 0)
	{
		best_manh_dst = 1000;
		return (true);
	}
	(game->reset == 0) ?
	reset_values(&best_coord[1], &best_coord[0], &best_manh_dst) : 1;
	coord[0] = *y;
	coord[1] = *x;
	closest_enemy_spot(map, coord, best_coord, &best_manh_dst);
	game->reset = (game->stop_checking) ? 0 : 1;
	return (false);
}