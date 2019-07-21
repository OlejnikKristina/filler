/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_figure.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: krioliin <krioliin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/30 15:19:11 by krioliin       #+#    #+#                */
/*   Updated: 2019/07/20 20:57:29 by krioliin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

void	read_figure(t_figure *figure)
{
	char	*line;
	int		y;

	get_next_line(STDIN_FILENO, &line);
	y = 0;
	figure->size_y = ft_atoi(&(line[ft_strlen("Piece ")]));
	figure->size_x = ft_atoi(&(line[ft_strlen("Piece ")
	+ count_digit64(figure->size_y) + 1]));
	ft_strdel(&line);
	figure->field = (char **)malloc(sizeof(char *) * figure->size_y + 1);
	ft_dprintf(fd_test, "--------- READ FIGURE --------\n");
	while (y < figure->size_y)
	{
		get_next_line(STDIN_FILENO, &line);
		figure->field[y] = ft_strdup(line);
		ft_dprintf(fd_test, "%s\n", figure->field[y]);
		y++;
		ft_strdel(&line);
	}
	figure->field[y] = NULL;
	cut_figure(figure);
}
