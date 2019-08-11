/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   find_spot.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: krioliin <krioliin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/28 17:49:50 by krioliin       #+#    #+#                */
/*   Updated: 2019/08/11 16:36:08 by krioliin      ########   odam.nl         */
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
	while (figure[fig_y])//24 + 4
	{
		while (figure[fig_y][fig_x]) //&& (x < map->max_x - fig->cut_x + 5))
		{
			if (map->max_x + 5 - fig->cut_x < x)
				return (false);
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

bool	closest_enemy_spot(t_map *map, int coord[2], 
		int best_coord[2], int *best_manht_dst)
{
	int			manh_dst;
	int			i;
	int			j;

	j = 0;
	i = 4;
	manh_dst = 1000;
	while (j < map->max_y)
	{
		while (i < map->max_x + 4)
		{
			if (map->map[j][i] == map->enemy)
			{
				if (manheten_dist(i, j, coord[1], coord[0]) <= manh_dst)
					manh_dst = manheten_dist(i, j, coord[1], coord[0]);
			}
			i++;
		}
		i = 4;
		j++;
	}
	if (manh_dst <= *best_manht_dst)
	{
		best_coord[0] = coord[0];
		best_coord[1]= coord[1];
		*best_manht_dst = manh_dst;
	}
	return ((*best_manht_dst == 0) ? 1 : 0);
}

/*
	my_coord[0] = y;
	my_coord[1] = x;
	best_coord[0] = y;
	best_coord[1] = x;
	Finding the closet position of enemy acording
	to my current coordinats
*/

bool	closest_pos(t_game *game, t_map *map, int *y, int *x)
{
	int static	best_coord[2];
	int			coord[2];
	int static	best_manh_dst;

	if (game->stop_checking)
	{
		*y = best_coord[0];
		*x = best_coord[1];
		//best_manh_dst = 1000;
		reset_values(&best_coord[1], &best_coord[0], &best_manh_dst);
		// best_coord[0] = 0;
		// best_coord[1] = 0;
	}
	if (best_manh_dst == 0)
	{
		best_manh_dst = 1000;
		return (true);
	}
	(game->reset == 0) ?
	reset_values(&best_coord[1], &best_coord[0], &best_manh_dst) : 1;
	coord[0] = *y;
	coord[1] = *x;
	closest_enemy_spot(map, coord, best_coord, &best_manh_dst);
	game->reset = (game->stop_checking) ? 0 : 1;
	return (0);
}


void	find_possible_spot(t_map *map, t_figure *figure, t_game *game)
{
	game->stop_checking = false;
	if (map->max_x <= 24)
	{
		if (((game->hit_right && game->hit_left) &&
		(game->hit_top || game->hit_bottom)))
			find_spots(map, figure, game, &closest_pos);
		else
			find_spots(map, figure, game, &surround_enemy);
	}
	else
		find_spots(map, figure, game, &closest_pos);
	ft_dprintf(fd_test, "r%dl%dt%db%d ",
	game->hit_right, game->hit_left, game->hit_top, game->hit_bottom);
}