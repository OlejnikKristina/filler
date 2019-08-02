/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   solver.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: krioliin <krioliin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/28 17:49:50 by krioliin       #+#    #+#                */
/*   Updated: 2019/08/02 15:34:28 by krioliin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

void	solver(t_map *map, t_game *game, t_figure *figure)
{
	closest_enemy_pos(game, map);
	if (PRINT)
	{
		game->target_hit = ft_strdup("Surround game!");
		game->square.x = 27;
		game->square.y = 12;
	}
	find_possible_spot(map, figure, game);
}
