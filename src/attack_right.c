/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   attack_right_wall.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: krioliin <krioliin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/08/04 10:14:35 by krioliin       #+#    #+#                */
/*   Updated: 2019/08/11 15:50:23 by krioliin      ########   odam.nl         */
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

bool			right_wall(t_game *game, t_map *map, int *y, int *x, bool reset)
{
	int static		pre_x;
	int static		pre_y;
	int static		manh_dst;

	// if (enemy_ran_top(game, map))
	// {
	// 	game->hit_right = true;
	// 	game->hit_top = false;
	// }
	(reset == 0) ? reset_values(&pre_x, &pre_y, &manh_dst) : 1;
	if (game->stop_checking)
	{
		*x = pre_x;
		*y = pre_y;
		reset_values(&pre_x, &pre_y, &manh_dst);
		//if ((map->max_x + 4 <= (game->fig_max_x + *x - 4)))//If it will hit top wall || (*y - game->fig_max_y <= 0)
		if ((map->max_x <= game->fig_max_x + *x))// 37 3
		{
			game->hit_right = true;
			ft_dprintf(fd_test, "Hit --> RIGHT WALL\n");
			return (true);
		}
		ft_dprintf(fd_test, "Target --> RIGHT WALL\n");
		return (false);
	}
	if (manheten_dist(map->max_x, target_rw(map, game, map->enemy), *x, *y) <= manh_dst)
	{
		ft_dprintf(fd_test, "Coord to check y%d x%d mnht %d\n",
		*y - y_cut_top, *x - x_cut_left - 4, manh_dst);
		pre_x = *x;
		pre_y = *y;
		manh_dst = manheten_dist(map->max_x, target_rw(map, game, map->enemy), *x, *y);
	}
	return (false);
}
