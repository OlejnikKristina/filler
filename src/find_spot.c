/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   find_spot.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: krioliin <krioliin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/28 17:49:50 by krioliin       #+#    #+#                */
/*   Updated: 2019/08/10 18:33:31 by krioliin      ########   odam.nl         */
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

bool	check_spot(char **figure, t_map *map, int y, int x, t_figure *fig)
{
	int		fig_x;
	int		fig_y;
	int		map_coord_x;
	bool	cover;
	int		print_figure = 0;

	fig_x = 0;
	fig_y = 0;
	cover = 0;
	map_coord_x = x;
	while (figure[fig_y])
	{
		while (figure[fig_y][fig_x])
		{
			if (map->map[y][x] != '.' && figure[fig_y][fig_x] == '*')
			{
				if (cover)
					return (false);
				else if (map->map[y][x] == map->player)
					cover = true;
				else if (map->map[y][x] == map->enemy)
					return (false);
			}
			if (print_figure == 2 && figure[fig_y][fig_x] == '*')
			{
				if (map->map[y][x] == '.')
					map->map[y][x] = '*';
				else
					map->map[y][x] = '$';
			}
			x++;
			fig_x++;
		}
		fig_x = 0;
		x = map_coord_x;
		fig_y++;
		y++;
	}
	return (cover);
}

bool	go_to_game(t_game *game, t_map *map, int *y, int *x)
{
	int static pre_x;
	int static pre_y;

	if (game->stop_checking)
	{
		*x = pre_x;
		*y = pre_y;
	}
	if (pre_x <= *x && pre_y <= *y)
	{
		if (*x <= game->square.x && *y <= game->square.y)
		{
			pre_x = *x;
			pre_y = *y;
		}
	}
	if (game->square.x - 12 <= *x && game->square.y - 5 <= *y)
		return (true);
	return (false);
}

bool	fill_map(t_game *game, t_map *map, int *y, int *x)
{
	if (game || map || *x || *y)
		return (true);
	return (true);
}

void	find_spots(t_map *map, t_figure *figure,
		t_game *game, bool (*algorithm)(t_game *, t_map *, int *, int *))
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
				if (algorithm(game, map, &y, &x))
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
	game->stop_checking = true;
	algorithm(game, map, &y, &x);
	ft_printf("%d %d\n", y - cut_y_top(figure), x - cut_x_left(figure) - 4);

	ft_dprintf(fd_test, "spot 2(y %d; x %d)\n",
	y - cut_y_top(figure), 
	x - cut_x_left(figure) - 4);
}

void	find_possible_spot(t_map *map, t_figure *figure, t_game *game)
{
	// t_coord		*prior_spots[500];
	// bool		spot_found;

	// spot_found = 0;
	// ft_bzero(&prior_spots, sizeof(prior_spots) * 500);
	game->stop_checking = false;
	// if (check_priority_spots(map, prior_spots))
	// {
	// 	if (find_prior_spt(map, figure, game, prior_spots))
	// 		spot_found = 1;
	// }
	if ((game->hit_right || game->hit_left) &&
		(game->hit_top || game->hit_bottom)) //&& !spot_found)
		find_spots(map, figure, game, &fill_map);
	else
		find_spots(map, figure, game, &surround_enemy);
	
	ft_dprintf(fd_test, "r%dl%dt%db%d ",
	game->hit_right, game->hit_left, game->hit_top, game->hit_bottom);
}