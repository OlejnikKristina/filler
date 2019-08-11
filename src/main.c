/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: krioliin <krioliin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/28 17:49:50 by krioliin       #+#    #+#                */
/*   Updated: 2019/08/11 19:42:02 by krioliin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"
/*
if (PRINT)
{
	enemy->target_hit = 1;
	enemy->square.x = 31;
	enemy->square.y = 14;
}
*/
void	init_player(t_map *map)
{
	char	*line;

	get_next_line(STDIN_FILENO, &line);
	map->player = (ft_strstr(line, "p1")) ? 'O' : 'X';
	map->enemy = (map->player == 'O') ? 'X' : 'O';
	ft_strdel(&line);
}

void		init_map_size(t_map *map)
{
	char	*line;

	get_next_line(STDIN_FILENO, &line);
	map->max_y = ft_atoi(&line[ft_strlen("Plateau ")]);
	map->max_x = ft_atoi(&line[ft_strlen("Plateau ")
	+ ft_count_digit(map->max_y)] + 1);
	ft_strdel(&line);
}

int		main()
{
	t_map		map;
	t_figure	figure;
	t_game		game;

	init_player(&map);
	init_map_size(&map);
	ft_bzero((void *)&game, sizeof(game));
	fd_test = open(TEST_FILE, O_RDWR);
	while (1)
	{
		if (read_map(&map) == false)
			return (0);
		read_figure(&figure, &game);
		game.fig_max_x = ft_strlen(figure.cut_fig[0]);
		game.fig_max_y = figure.cut_y;
		find_possible_spot(&map, &figure, &game);
		clean_data(&map, &figure, &game);
	}
	return (0);
}
