/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   additional_funcs.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: krioliin <krioliin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/28 17:49:50 by krioliin       #+#    #+#                */
/*   Updated: 2019/08/12 00:04:33 by krioliin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

void	increment(int *increment_me, int *add_plus_one)
{
	*increment_me += 1;
	*add_plus_one += 1;
}

short	max_y_filed(t_map *map, char **cut_figure)
{
	int		y;

	y = 0;
	while (cut_figure[y])
		y++;
	return (map->max_y - y);
}

void	set_to_null(int *set_me_null, int *and_me, bool *me_as_well)
{
	*set_me_null = 0;
	*and_me = 0;
	*me_as_well = 0;
}
