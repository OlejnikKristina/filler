/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   find_spot.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: krioliin <krioliin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/28 17:49:50 by krioliin       #+#    #+#                */
/*   Updated: 2019/07/31 19:39:24 by krioliin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

bool	print_spot(char **figure, t_map *map, int map_y, int map_x, t_figure *fig)
{
	int		fig_x;
	int		fig_y;
	int		map_coord_x;
	bool	cover;
	int		print_figure = 2;

	fig_x = 0;
	fig_y = 0;
	cover = 0;
	map_coord_x = map_x;
	// (PRINT && map_y == (15 + cut_y_top(fig))  && map_x == (25 + cut_x_left(fig) + 4))
	// ? (print_figure = 2) : 0;
	while (figure[fig_y])
	{
		while (figure[fig_y][fig_x])
		{
			if (map->map[map_y][map_x] != '.' && figure[fig_y][fig_x] == '*')
			{
				if (cover)
					return (false);
				else if (map->map[map_y][map_x] == 'O')
					cover = true;
			}
			if (print_figure == 2 && figure[fig_y][fig_x] == '*')
			{
				if (map->map[map_y][map_x] == '.')
					map->map[map_y][map_x] = '*';
				else
					map->map[map_y][map_x] = '$';
			}
			map_x++;
			fig_x++;
		}
		fig_x = 0;
		map_x = map_coord_x;
		fig_y++;
		map_y++;
	}
	return (cover);
}

/*
** {coord_x coord_y}
** Coordinate on the map
** which we are checking
** for possibility to put
** a figure
*/

bool	check_spot(char **figure, t_map *map, int map_y, int map_x, t_figure *fig)
{
	int		fig_x;
	int		fig_y;
	int		map_coord_x;
	bool	cover;
	int		print_figure = 0;

	fig_x = 0;
	fig_y = 0;
	cover = 0;
	map_coord_x = map_x;
	// (PRINT && map_y == (15 + cut_y_top(fig))  && map_x == (25 + cut_x_left(fig) + 4))
	// ? (print_figure = 2) : 0;
	while (figure[fig_y])
	{
		while (figure[fig_y][fig_x])
		{
			if (map->map[map_y][map_x] != '.' && figure[fig_y][fig_x] == '*')
			{
				if (cover)
					return (false);
				else if (map->map[map_y][map_x] == 'O')
					cover = true;
			}
			if (print_figure == 2 && figure[fig_y][fig_x] == '*')
			{
				if (map->map[map_y][map_x] == '.')
					map->map[map_y][map_x] = '*';
				else
					map->map[map_y][map_x] = '$';
			}
			map_x++;
			fig_x++;
		}
		fig_x = 0;
		map_x = map_coord_x;
		fig_y++;
		map_y++;
	}
	return (cover);
}

bool	go_to_enemy(t_enemy *enemy, t_map *map, int *y, int *x)
{
	int static pre_x = 0;
	int static pre_y = 0;

	if (enemy->stop_checking)
	{
		*x = pre_x;
		*y = pre_y;
	}
	if (pre_x <= *x && pre_y <= *y)
	{
		if (*x <= enemy->square.x && *y <= enemy->square.y)
		{
			pre_x = *x;
			pre_y = *y;
		}
	}
	if (enemy->square.x - 12 <= *x && enemy->square.y - 5 <= *y)
	{
		enemy->target = ft_strdup("Surround enemy!");
		return (true);
	}
	return (false);
}

bool	fill_map(t_enemy *enemy, t_map *map, int *y, int *x)
{
	if (enemy || map || *x || *y)
		return (true);
	return (true);
}

void	find_spots(t_map *map, t_figure *figure,
		t_enemy *enemy, bool (*algorithm)(t_enemy *, t_map *, int *, int *))
{
	int		y;
	int		x;
	int		max_y_field;

	y = 0;
	x = 4;
	max_y_field = max_y_filed(map, figure->cut_fig + 1);
	y_cut_top = cut_y_top(figure);
	x_cut_left = cut_x_left(figure);
	while (y < max_y_field)
	{
		while (x < map->max_x + 4)
		{
			if (check_spot(figure->cut_fig, map, y, x, figure))
			{
				if (algorithm(enemy, map, &y, &x))
				{
					ft_printf("%d %d\n", y - cut_y_top(figure),
					 x - cut_x_left(figure) - 4);
					ft_dprintf(fd_test, "spot 1(y %d; x %d)\n",
					y - cut_y_top(figure), x - cut_x_left(figure) - 4);
					//print_spot(figure->cut_fig, map, y, x, figure);
					return ;
				}
			}
			x++;
		}
		x = 4;
		y++;
	}
	enemy->stop_checking = true;
	algorithm(enemy, map, &y, &x);
	ft_printf("%d %d\n", y - cut_y_top(figure), x - cut_x_left(figure) - 4);
	ft_dprintf(fd_test, "spot 2(y %d; x %d)\n",
	y - cut_y_top(figure), 
	x - cut_x_left(figure) - 4);
}


void	find_possible_spot(t_map *map, t_figure *figure, t_enemy *enemy)
{
	enemy->stop_checking = false;
	if ((enemy->hit_right || enemy->hit_left) &&
		(enemy->hit_top || enemy->hit_bottom))
		find_spots(map, figure, enemy, &fill_map);
	else
	{
		figure_view(figure, enemy);
		find_spots(map, figure, enemy, &surround_enemy);
	}
}