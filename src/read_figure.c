/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_figure.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: krioliin <krioliin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/30 15:19:11 by krioliin       #+#    #+#                */
/*   Updated: 2019/08/14 13:56:14 by krioliin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	read_figure(t_figure *figure, t_game *game)
{
	char	*line;
	int		y;

	get_next_line(STDIN_FILENO, &line);
	y = 0;
	figure->size_y = ft_atoi(&(line[ft_strlen("Piece ")]));
	figure->size_x = ft_atoi(&(line[ft_strlen("Piece ")
	+ count_digit64(figure->size_y) + 1]));
	ft_strdel(&line);
	figure->field = (char **)ft_memalloc(sizeof(char *) * figure->size_y + 1);
	while (y < figure->size_y)
	{
		get_next_line(STDIN_FILENO, &line);
		figure->field[y] = ft_strdup(line);
		y++;
		ft_strdel(&line);
	}
	figure->field[y] = NULL;
	cut_figure(figure);
	game->fig_max_x = ft_strlen(figure->cut_fig[0]);
	game->fig_max_y = figure->cut_y;
}
