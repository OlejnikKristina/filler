/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: krioliin <krioliin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/28 17:49:50 by krioliin       #+#    #+#                */
/*   Updated: 2019/07/23 23:01:05 by krioliin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"
/*
if (PRINT)
{
	enemy->target_struck = 1;
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
	t_enemy		enemy;
	int			i;

	i = 0;
	fd_test = open(TEST_FILE, O_RDWR);
	if (PRINT)
	{
		close(0);
		open(TEST_MAP, O_RDONLY);
	}
	init_player(&map);
	init_map_size(&map);
	enemy.target_struck = 0;
	while (1)
	{
		ft_dprintf(fd_test, "\n\n***** Run loop %d time ****\n", i + 1);
		if (read_map(&map) == false)
		{
			ft_dprintf(fd_test, "Can not read from stdin\n");
			return (0);
		}
		read_figure(&figure);
		closest_enemy_pos(&enemy, &map);
		if (PRINT)
		{
			enemy.target_struck = 1;
			enemy.square.x = 31;
			enemy.square.y = 14;
		}
		(PRINT) ? map_print(&map) : 1;
		find_possible_spot(&map, &figure, &enemy);
		//	solver(&map, &enemy, &figure);
		//find_possible_spot(&map, &figure, &enemy);
		(PRINT) ? map_print(&map) : 1;
		clean_data(&map, &figure);
		i++;
	}
	return (0);
}
