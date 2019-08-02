/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   closest_game_pos.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: krioliin <krioliin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/28 17:49:50 by krioliin       #+#    #+#                */
/*   Updated: 2019/07/26 11:11:47 by krioliin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

/*
**
**	int	right_bottom_x;
**	int	right_bottom_y;
**	check_x(1, map->map[y], map->enemy);
**
*/

bool		is_enemy(int y, int x, t_map *map, t_game *game, int hey)
{
	if (map->map[y][x] == map->enemy && !game->stop_checking && hey)
	{
		game->left.x = x;
		game->left.y = y;
		game->stop_checking = true;
		return (true);
	}
	else if (map->map[y][x] == map->enemy)
	{
		game->right.x = x;
		game->right.y = y;
		return (true);
	}
	return (false);
}

bool		max_left(t_game *game, t_map *map, int y_const, int x_const)
{
	int		x;
	int		y;

	x = x_const;
	y = y_const;
	while (0 <= y)
	{
		if (is_enemy(y, x_const, map, game, 1) || is_enemy(y_const, x, map, game, 1))
			return (true);

		x++;
		y--;
	}
	if ( -1 != findchr(map->map[y_const], map->enemy))
	{
		game->left.x = findchr(map->map[y_const], map->enemy);
		game->left.y = y_const;
		return (true);
	}
	return (false);
}

bool	max_right(t_game *game, t_map *map, int y_const, int x_const)
{
	int		x;
	int		y;

	x = x_const;
	y = y_const;
	while (y < map->max_y)
	{
		if (is_enemy(y, x_const, map, game, 0) || is_enemy(y_const, x, map, game, 0))
			return (true);
		x--;
		y++;
	}
	if ( -1 != findchr(map->map[y_const], map->enemy))
	{
		game->right.x = findchr(map->map[y_const], map->enemy);
		game->right.y = y_const;
		return (true);
	}
	return (false);
}

void	closest_enemy_pos(t_game *game, t_map *map)
{
	int		y;
	int		x;

	y = map->max_y - 1;
	x = 0;
	while (!max_left(game, map, y, x) && y)
	{
		y--;
		x++;
	}
	x = map->max_x + 3;
	y = 0;
	while (!max_right(game, map, y, x) && y <= map->max_y)
	{
		y++;
		x--;
	}
	game->square.x = game->left.x;
	game->square.y = game->right.y;

	game->stop_checking = false;
	ft_dprintf(fd_test, "MAX LEFT: (x %d; y %d)\n",
		game->left.x - 4, game->left.y);
	ft_dprintf(fd_test, "MAX RIGHT: (x %d; y %d)\n",
		game->right.x - 4, game->right.y);

	ft_dprintf(fd_test, "game->square: (x %d; y %d)\n",
	game->square.x - 4, game->square.y);

}
