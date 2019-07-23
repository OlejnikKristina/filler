/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   solver.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: krioliin <krioliin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/28 17:49:50 by krioliin       #+#    #+#                */
/*   Updated: 2019/07/23 17:55:55 by krioliin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

void	solver(t_map *map, t_enemy *enemy, t_figure *figure)
{
	//closest_enemy_pos(enemy, map);
	if (PRINT)
	{
		enemy->target_struck = 1;
		enemy->square.x = 27;
		enemy->square.y = 12;
	}
	find_possible_spot(map, figure, enemy);
}
