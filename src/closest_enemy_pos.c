/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   closest_enemy_pos.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: krioliin <krioliin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/28 17:49:50 by krioliin       #+#    #+#                */
/*   Updated: 2019/07/21 23:07:29 by krioliin      ########   odam.nl         */
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

// int		check_x(int	x_start, char *check_line, char enemy_sign)
// {
// 	static int x;

// 	x += x_start;
// 	if (check_line[x] == enemy_sign)
// 	{
// 		ft_dprintf(fd_test, "closest_enemy_pos x = %d)\n", x);
// 		return (x);
// 	}
// 	ft_dprintf(fd_test, "Enemy not found x = %d)\n", x);
// 	return (-1);
// }

bool		is_enemy(int y, int x, t_map *map, t_enemy *enemy)
{
	static bool check_max_right;

	if (map->map[y][x] == map->enemy && !check_max_right)
	{
		enemy->left.x = x;
		enemy->left.y = y;
		check_max_right = true;
		return (true);
	}
	else if (map->map[y][x] == map->enemy)
	{
		enemy->right.x = x;
		enemy->right.y = y;
	}
	return (false);
}

bool		max_left(t_enemy *enemy, t_map *map, int y_const, int x_const)
{
	int		x;
	int		y;

	x = x_const;//0
	y = y_const;//23
	while (0 <= y)
	{
		if (is_enemy(y, x_const, map, enemy))
		{
			ft_dprintf(fd_test, "COLUMN X (x %d|y %d)\n", x_const - 4, y);
			return (true);
		}
		else if (is_enemy(y_const, x, map, enemy))
		{
			ft_dprintf(fd_test, "LINE Y CONST (x %d|y %d)\n",
			enemy->left.x - 4, enemy->left.y);
			return (true);
		}
		x++;
		y--;
	}
	if ( -1 != findchr(map->map[y_const], map->enemy))
	{
		enemy->left.x = findchr(map->map[y_const], map->enemy);
		enemy->left.y = y_const;
		ft_dprintf(fd_test, "MAX LEFT: (x %d; y %d)\n",
		enemy->left.x - 4, enemy->left.y);
		return (true);
	}
	return (false);
}

bool	max_right(t_enemy *enemy, t_map *map, int y_const, int x_const)
{
	int		x;
	int		y;

	x = x_const;//39
	y = y_const;//0 
	while (y < map->max_y)
	{
		if (is_enemy(y, x_const, map, enemy))
		{
			ft_dprintf(fd_test, "COLUMN X (x %d|y %d)\n", x_const - 4, y);
			return (true);
		}
		else if (is_enemy(y_const, x, map, enemy))
		{
			ft_dprintf(fd_test, "LINE Y CONST (x %d|y %d)\n",
			enemy->right.x - 4, enemy->right.y);
			return (true);
		}
		x--;
		y++;
	}
	if ( -1 != findchr(map->map[y_const], map->enemy))
	{
		enemy->right.x = findchr(map->map[y_const], map->enemy);
		enemy->right.y = y_const;
		ft_dprintf(fd_test, "MAX RIGHT: (x %d; y %d)\n",
		enemy->right.x - 4, enemy->right.y);
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
	ft_dprintf(fd_test, "enemy->square: (x %d; y %d)\n",
	enemy->square.x, enemy->square.y);
	enemy->target_struck = 0;
}
