/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   clean_data.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: krioliin <krioliin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/28 17:49:50 by krioliin       #+#    #+#                */
/*   Updated: 2019/08/11 19:03:45 by krioliin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

void		free_arr(void ***arr, size_t len)
{
	short int	i;

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

void	field_del(char **str, int size)
{
	int		i;

	i = 0;
	if (!*str || !str)
		return ;
	while (i < size)
	{
		if (str[i])
			ft_strdel(&str[i]);
		i++;
	}
	ft_strdel(str);
	str = NULL;
}

void	clean_data(t_map *map, t_figure *figure, t_game *game)
{
	free_arr((void ***)&(map->map), map->max_y);
	free_arr((void ***)&(figure->field), figure->size_y);
	cut_figure_del(figure);
}