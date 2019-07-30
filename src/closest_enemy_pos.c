/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   closest_enemy_pos.c                                :+:    :+:            */
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

bool		is_enemy(int y, int x, t_map *map, t_enemy *enemy, int hey)
{
	if (map->map[y][x] == map->enemy && !enemy->stop_checking && hey)
	{
		enemy->left.x = x;
		enemy->left.y = y;
		enemy->stop_checking = true;
		return (true);
	}
	else if (map->map[y][x] == map->enemy)
	{
		enemy->right.x = x;
		enemy->right.y = y;
		return (true);
	}
	return (false);
}

bool		max_left(t_enemy *enemy, t_map *map, int y_const, int x_const)
{
	int		x;
	int		y;

	x = x_const;
	y = y_const;
	while (0 <= y)
	{
		if (is_enemy(y, x_const, map, enemy, 1) || is_enemy(y_const, x, map, enemy, 1))
			return (true);

		x++;
		y--;
	}
	if ( -1 != findchr(map->map[y_const], map->enemy))
	{
		enemy->left.x = findchr(map->map[y_const], map->enemy);
		enemy->left.y = y_const;
		return (true);
	}
	return (false);
}

bool	max_right(t_enemy *enemy, t_map *map, int y_const, int x_const)
{
	int		x;
	int		y;

	x = x_const;
	y = y_const;
	while (y < map->max_y)
	{
		if (is_enemy(y, x_const, map, enemy, 0) || is_enemy(y_const, x, map, enemy, 0))
			return (true);
		x--;
		y++;
	}
	if ( -1 != findchr(map->map[y_const], map->enemy))
	{
		enemy->right.x = findchr(map->map[y_const], map->enemy);
		enemy->right.y = y_const;
		return (true);
	}
	return (false);
}

void	closest_enemy_pos(t_enemy *enemy, t_map *map)
{
	int		y;
	int		x;

	y = map->max_y - 1;
	x = 0;
	while (!max_left(enemy, map, y, x) && y)
	{
		y--;
		x++;
	}
	x = map->max_x + 3;
	y = 0;
	while (!max_right(enemy, map, y, x) && y <= map->max_y)
	{
		y++;
		x--;
	}
	enemy->square.x = enemy->left.x;
	enemy->square.y = enemy->right.y;

	enemy->stop_checking = false;
	ft_dprintf(fd_test, "MAX LEFT: (x %d; y %d)\n",
		enemy->left.x - 4, enemy->left.y);
	ft_dprintf(fd_test, "MAX RIGHT: (x %d; y %d)\n",
		enemy->right.x - 4, enemy->right.y);

	ft_dprintf(fd_test, "enemy->square: (x %d; y %d)\n",
	enemy->square.x - 4, enemy->square.y);

}
