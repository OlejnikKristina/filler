/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   max_xy_field.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: krioliin <krioliin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/28 17:49:50 by krioliin       #+#    #+#                */
/*   Updated: 2019/07/21 23:33:42 by krioliin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

int		max_x_filed(t_map *map, char *figure)
{
	return (map->max_x - ft_strlen(figure));
}

short		max_y_filed(t_map *map, char **figure)
{
	int		y;

	y = 0;
	while (figure[y])
		y++;
	return (map->max_y - y);
}
