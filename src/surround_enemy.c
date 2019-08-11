/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   surround_enemy.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: krioliin <krioliin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/28 17:49:50 by krioliin       #+#    #+#                */
/*   Updated: 2019/08/12 00:00:02 by krioliin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

void	reset_values(int *pre_x, int *pre_y, int *manh_dst)
{
	*pre_x = 0;
	*pre_y = 0;
	*manh_dst = 1000;
}

/*
** Creat a strcut with info where your player
** shold go according to enemy position
**
** if current Manheten disctance is the same as previous one
** check coordinate as well
**
** my coord: A(x,y) target B(i, j)
** distance = |i - x| + |j - y|
*/

int		manheten_dist(int i, int j, int x, int y)
{
	int		first_mod;
	int		second_mod;

	if (i == -1)
		return (-1);
	first_mod = i - x;
	if (first_mod < 0)
		first_mod *= -1;
	second_mod = j - y;
	if (second_mod < 0)
		second_mod *= -1;
	return (first_mod + second_mod);
}

bool	attack_right_left(t_game *game, t_map *map, int **yx)
{
	if (ENEMY_FROM_RIGHT)
	{
		if (right_wall(game, map, yx, game->reset))
			return (true);
	}
	else
	{
		if (left_wall(game, map, yx, game->reset))
			return (true);
	}
	return (false);
}

bool	attack_top_bottom(t_game *game, t_map *map, int **yx)
{
	if (ENEMY_FROM_BOTTOM)
	{
		if (bottom(game, map, yx, game->reset))
			return (true);
	}
	else
	{
		if (top(game, map, yx, game->reset))
			return (true);
	}
	return (false);
}

bool	surround_enemy(t_game *game, t_map *map, int *y, int *x)
{
	int		*yx[2];

	yx[0] = y;
	yx[1] = x;
	if (((game->fig_max_y < game->fig_max_x)
	&& (!game->hit_right && !game->hit_left)) ||
		(game->hit_top || game->hit_bottom))
	{
		if (attack_right_left(game, map, yx))
			return (true);
	}
	else
	{
		if (attack_top_bottom(game, map, yx))
			return (true);
	}
	game->reset = (game->stop_checking) ? 0 : 1;
	return (false);
}
