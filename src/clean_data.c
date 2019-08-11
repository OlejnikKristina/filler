/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   clean_data.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: krioliin <krioliin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/28 17:49:50 by krioliin       #+#    #+#                */
/*   Updated: 2019/08/12 00:00:24 by krioliin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

void	free_arr(void ***arr, int len)
{
	int	i;

	i = 0;
	if (!**arr || !*arr || !arr)
		return ;
	while (i < len)
	{
		if ((*arr)[i])
		{
			free((*arr)[i]);
			(*arr)[i] = NULL;
		}
		i++;
	}
	free(*arr);
	*arr = NULL;
}

void	cut_figure_del(t_figure *figure)
{
	int		y;

	y = 0;
	if (!figure->cut_fig)
		return ;
	while (y < figure->cut_y)
		y++;
	if (figure->cut_fig)
		free_arr((void ***)&(figure->cut_fig), y);
	figure->cut_fig = NULL;
}

void	clean_data(t_map *map, t_figure *figure)
{
	free_arr((void ***)&(map->map), map->max_y);
	free_arr((void ***)&(figure->field), figure->size_y);
	cut_figure_del(figure);
}
