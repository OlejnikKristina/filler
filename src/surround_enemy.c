/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   surround_game.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: krioliin <krioliin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/28 17:49:50 by krioliin       #+#    #+#                */
/*   Updated: 2019/08/02 15:19:09 by krioliin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

void	reset_values(int *pre_x, int *pre_y, int *manh_dst)
{
	*pre_x = 0;
	*pre_y = 0;
	*manh_dst = 1000;
}

char	figure_view(t_game *game)
{
	if (game->fig_max_y < game->fig_max_x)
		return ('h');
	else
		return ('v');
}

// from vm spot				<got (O): [y0, x-5]
// from test map spot		y13;x21;
// mine choosen best spot	y15;x18

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
	int 		first_mod;
	int 		second_mod;

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

bool	surround_enemy(t_game *game, t_map *map, int *y, int *x)
{

		if ((figure_view(game) == 'h' && (!game->hit_right && !game->hit_left)) ||
			(game->hit_top || game->hit_bottom))
		{
			if (ENEMY_FROM_RIGHT)
			{
				if (right_wall(game, map, y, x, game->reset))
					return (true);
			}
			else
				if (left_wall(game, map, y, x, game->reset))
					return (true);
		}
		else
		{
			if (ENEMY_FROM_BOTTOM)
			{
				if (bottom(game, map, y, x, game->reset))
					return (true);
			}
			else
			{
				if (top(game, map, y, x, game->reset))
					return (true);
			}
		}
//	}
	game->reset = (game->stop_checking) ? 0 : 1;
	game->stop_checking = false;
	return (false);
}