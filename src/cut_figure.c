/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cut_figure.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: krioliin <krioliin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/28 17:49:50 by krioliin       #+#    #+#                */
/*   Updated: 2019/08/10 22:58:06 by krioliin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

short unsigned	cut_x_left(t_figure *figure)
{
	int				y;
	int				x;
	short unsigned	cut_columns;
	bool			star;

	y = 0;
	x = 0;
	cut_columns = 0;
	star = 0;
	while (x < figure->size_x)
	{
		while (y < figure->size_y)
		{
			if (figure->field[y][x] == '*')
				star = true;
			y++;
		}
		if (star)
			break ;
		cut_columns++;
		y = 0;
		x++;
	}
	return (cut_columns);
}

short unsigned cut_x_right(t_figure *figure)
{
	short unsigned	cut_columns;
	int				y;
	int				max_x;
	int				max_y;
	bool			star;

	cut_columns = 0;
	max_x = figure->size_x;
	max_y = figure->size_y;
	star = 0;
	y = 0;
	while (max_x)
	{
		max_x--;
		y = 0;
		while (y < max_y)
		{
			if (figure->field[y][max_x] == '*')
				star = true;
			y++;
		}
		if (star)
			break ;
		cut_columns++;
	}
	return (cut_columns);
}

int	cut_y_top(t_figure *figure)
{
	short unsigned	cut_rows;
	int				max_y;
	int				y;

	max_y = figure->size_y;
	cut_rows = 0;
	y = 0;
	while (y < max_y)
	{
		if (ft_strchr(figure->field[y], '*'))
			break ;
		cut_rows++;
		y++;
	}
	return (cut_rows);
}

short unsigned	cut_y_bottom(t_figure *figure)
{
	short unsigned	cut_rows;
	int				max_y;

	cut_rows = 0;
	max_y = figure->size_y;
	while (max_y)
	{
		max_y--;
		if (ft_strchr(figure->field[max_y], '*'))
			break ;
		cut_rows++;
	}
	return (cut_rows);
}

/*
**left_offset=2;
**	  ⬇	 max_fig_x=1;
**	  ⬇	  ⬇
**	|. .|. .|.|⬅ cut_y_top	|2
**	|. .|. .|.|⬅ cut_y_top	|
**	|. .|* *|.|⬅ max_fig_y	|2
**	|. .|* .|.|⬅ max_fig_y	|
**	|. .|. .|.|⬅ cut_y_bottom|1
**
*/

void	cut_figure(t_figure *figure)
{
	int		max_fig_x;
	int		max_fig_y;
	int		y;
	int		index;
	int		left_offset;

	index = 0;
	y = cut_y_top(figure);
	left_offset = cut_x_left(figure);
	max_fig_y = figure->size_y - cut_y_top(figure) - cut_y_bottom(figure);
	max_fig_x = figure->size_x - cut_x_left(figure) - cut_x_right(figure);
	figure->cut_x = max_fig_x;
	figure->cut_fig = (char **)malloc(sizeof(char *) * max_fig_y + 2);
	while (y < figure->size_y - cut_y_bottom(figure))
	{
		figure->cut_fig[index] = ft_strsub(figure->field[y], left_offset, max_fig_x);
		index++;
		y++;
	}
	figure->cut_y = index;
	figure->cut_fig[index] = NULL;
}
