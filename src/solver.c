/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   solver.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: krioliin <krioliin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/28 17:49:50 by krioliin       #+#    #+#                */
/*   Updated: 2019/07/26 16:00:44 by krioliin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

void	solver(t_map *map, t_enemy *enemy, t_figure *figure)
{
	closest_enemy_pos(enemy, map);
	if (PRINT)
	{
		enemy->target_hit = ft_strdup("Surround enemy!");
		enemy->square.x = 27;
		enemy->square.y = 12;
	}
	find_possible_spot(map, figure, enemy);
}
