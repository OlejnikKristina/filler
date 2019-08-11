/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: krioliin <krioliin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/28 17:49:50 by krioliin       #+#    #+#                */
/*   Updated: 2019/08/11 21:12:20 by krioliin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

void	init_player(t_map *map)
{
	char	*line;

	get_next_line(STDIN_FILENO, &line);
	map->player = (ft_strstr(line, "p1")) ? 'O' : 'X';
	map->enemy = (map->player == 'O') ? 'X' : 'O';
	ft_strdel(&line);
}

void	init_map_size(t_map *map)
{
	char	*line;

	get_next_line(STDIN_FILENO, &line);
	map->max_y = ft_atoi(&line[ft_strlen("Plateau ")]);
	map->max_x = ft_atoi(&line[ft_strlen("Plateau ")
	+ ft_count_digit(map->max_y)] + 1);
	ft_strdel(&line);
}

int		main(void)
{
	t_map		map;
	t_figure	figure;
	t_game		game;

	init_player(&map);
	init_map_size(&map);
	ft_bzero((void *)&game, sizeof(game));
	while (1)
	{
		if (!read_map(&map))
			return (0);
		read_figure(&figure, &game);
		find_possible_spot(&map, &figure, &game);
		clean_data(&map, &figure);
	}
	return (0);
}
