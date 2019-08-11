/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   find_spot.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: krioliin <krioliin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/28 17:49:50 by krioliin       #+#    #+#                */
/*   Updated: 2019/08/11 23:39:57 by krioliin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

bool	superimpose(char map_chr, bool *cover, t_map *map)
{
	if (*cover)
		return (false);
	else if (map_chr == map->player)
		*cover = true;
	else if (map_chr == map->enemy)
		return (false);
	return (true);
}

/*
** {coord_x coord_y}
** Coordinate on the map  which we are checking
** for possibility to put a figure
*/

bool	check_spot(t_map *map, int y, int x, t_figure *f)
{
	int		fig_x;
	int		fig_y;
	int		map_coord_x;
	bool	cover;

	set_to_null(&fig_x, &fig_y, &cover);
	map_coord_x = x;
	while (f->cut_fig[fig_y])
	{
		while (f->cut_fig[fig_y][fig_x])
		{
			if (map->max_x + 5 - f->cut_x < x)
				return (false);
			if (map->map[y][x] != '.' && f->cut_fig[fig_y][fig_x] == '*')
			{
				if (!superimpose(map->map[y][x], &cover, map))
					return (false);
			}
			increment(&x, &fig_x);
		}
		fig_x = 0;
		x = map_coord_x;
		increment(&y, &fig_y);
	}
	return (cover);
}

void	print_result(t_game *game, t_figure *figure, int y, int x)
{
	y = y - cut_y_top(figure);
	x = x - cut_x_left(figure) - 4;
	ft_putnbr(y);
	ft_putchar(' ');
	ft_putnbr(x);
	ft_putchar('\n');
	game->stop_checking = false;
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
	while (y < max_y_field)
	{
		while (x < map->max_x + 4)
		{
			if (check_spot(map, y, x, figure) && (algorithm(game, map, &y, &x)))
			{
				print_result(game, figure, y, x);
				return ;
			}
			x++;
		}
		x = 4;
		y++;
	}
	game->stop_checking = true;
	algorithm(game, map, &y, &x);
	print_result(game, figure, y, x);
}

void	find_possible_spot(t_map *map, t_figure *figure, t_game *game)
{
	game->stop_checking = false;
	if (map->max_y <= 24)
	{
		if (((game->hit_right || game->hit_left) &&
			(game->hit_top || game->hit_bottom)))
			find_spots(map, figure, game, &closest_to_enemy_pos);
		else
			find_spots(map, figure, game, &surround_enemy);
	}
	else
		find_spots(map, figure, game, &closest_to_enemy_pos);
}
