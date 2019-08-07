/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   attack_left_wall.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: krioliin <krioliin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/08/04 10:14:27 by krioliin       #+#    #+#                */
/*   Updated: 2019/08/04 11:57:33 by krioliin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

bool	left_wall(t_game *game, t_map *map, int *y, int *x, bool reset)
{
	int static		pre_x;
	int static		pre_y;
	int static		manh_dst;

	(reset == 0) ? reset_values(&pre_x, &pre_y, &manh_dst) : 1;
	if (game->stop_checking)
	{
		*x = pre_x;
		*y = pre_y;
		reset_values(&pre_x, &pre_y, &manh_dst);
		if (*x <= 4)
		{
			game->hit_left = true;
			ft_dprintf(fd_test, "Hit --> LEFT WALL\n");
			return (true);
		}
		ft_dprintf(fd_test, "Target --> LEFT WALL\n");
		return (false);
	}
	if (manheten_dist(4, target_rw(map, map->enemy), *x, *y) <= manh_dst)
	{
		pre_x = *x;
		pre_y = *y;
		manh_dst = manheten_dist(map->max_x, target_rw(map, map->enemy), *x, *y);
	}
	return (false);
}
