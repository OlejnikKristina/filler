/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   surround_game.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: krioliin <krioliin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/28 17:49:50 by krioliin       #+#    #+#                */
/*   Updated: 2019/08/02 15:19:09 by krioliin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

void	reset_values(int *pre_x, int *pre_y, int *manh_dst)
{
	*pre_x = 0;
	*pre_y = 0;
	*manh_dst = 1000;
}

char	figure_view(t_game *game)
{
	if (game->fig_max_y < game->fig_max_x)
		return ('h');
	else
		return ('v');
}

// from vm spot				<got (O): [y0, x-5]
// from test map spot		y13;x21;
// mine choosen best spot	y15;x18

int		target_rw(t_map *map, char game_chr)
{
	int		y;

	y = 0;
	while (y < map->max_y)
	{
		if (ft_strchr(map->map[y], game_chr))
		{
			(y != 0) ? y-- : 1;
			(y != 0) ? y-- : 1;
			return (y);
		}
		y++;
	}
	return (y);
}

/*
** Creat a strcut with info where your player 
** shold go according to enemy position
**
** if current Manheten disctance is the same as previous one
** check coordinate as well
**
** my coord: A(x,y) target B(i, j)
** distance = |i - x| + |j - y|
*/

int		manheten_dist(int i, int j, int x, int y)
{
	int 		first_mod;
	int 		second_mod;

	first_mod = i - x;
	if (first_mod < 0)
		first_mod *= -1;
	second_mod = j - y;
	if (second_mod < 0)
		second_mod *= -1;
	return (first_mod + second_mod);
}

void	left_wall(t_game *game, t_map *map, int *y, int *x)
{
	int static		pre_x = 0;
	int static		pre_y = 0;

	if (game->stop_checking)
	{
		*x = pre_x;
		*y = pre_y;
		pre_x = 0;
		pre_y = 0;
	}
	if (pre_x <= *x && (pre_y <= *y))
	{
		pre_x = *x;
		pre_y = *y;
	}
	ft_dprintf(fd_test, " LEFT WALL\n");
}

int		target_bottom(t_map *map, char game_chr)
{
	int		x;
	int		y;
	bool	game_right;

	y = 0;
	x = 4;
	while (x < map->max_x + 4)
	{
		while (y < map->max_y)
		{
			if (map->map[y][x] == game_chr)
			{
				(x != 0) ? x-- : 1;
				(x != 0) ? x-- : 1;
				return (x);
			}
			y++;
		}
		y = 0;
		x++;
	}
	return (x);
}

int		target_top_x(t_map *map, char enemy_chr, bool enemy_from_right)
{
	short		x;
	short		y;
	short		my_topest_open_spot;

	y = 0;
	x = map->max_x;
	while (4 <= x)
	{
		while (y < map->max_y)
		{
			if (map->map[y][x] == map->player)
			{
				ft_dprintf(fd_test, "topest open right spot y%d x%d\n", y, x);
				return (x - 2);
			}
			if (map->map[y][x] == enemy_chr)
				break ;
			y++;
		}
		x--;
		y = 0;
	}
	return (x - 2);
}

bool	top(t_game *game, t_map *map, int *y, int *x, bool reset)
{
	int static		pre_x = 0;
	int static		pre_y = 0;
	int static		manhdst;

	if (reset == 0)
		reset_values(&pre_x, &pre_y, &manhdst);
	if (game->stop_checking)
	{
		*x = pre_x;
		*y = pre_y;
		reset_values(&pre_x, &pre_y, &manhdst);
		if (*y - game->fig_max_y <= 0)
		{
			game->hit_top = true;
			ft_dprintf(fd_test, "Hit target --> TOP\n");
			return (true);
		}
		ft_dprintf(fd_test, "Target --> TOP Final ManhDst: %d\n", manhdst);
		return (false);
	}
	if (manheten_dist(target_top_x(map, map->enemy, 1), 0, *x, *y) <= manhdst)
	{
		pre_x = *x;
		pre_y = *y;
		manhdst = manheten_dist(map->max_y, target_bottom(map, map->enemy), *x, *y);
	}
	return (false);
}

bool	enemy_ran_top(t_game *game, t_map *map)
{
	short int	enemy_topest_pos;
	short int	my_rightest_pos;
	short int	y;
	short int	x;

	y = 0;
	x = 0;
	while (y < map->max_y)
	{
		if (ft_strchr(map->map[y], map->enemy))
			enemy_topest_pos = y;
		y++;
	}
	y = 0;
	while (4 <= x)
	{
		while (y < map->max_y)
		{
			if (map->map[y][x] == map->player)
			{
				my_rightest_pos = y;
				break ;
			}
			y++;
		}
		x--;
		y = 0;
	}
	if (enemy_topest_pos < my_rightest_pos - 4)
		return (true);
	return (false);
}

bool	right_wall(t_game *game, t_map *map, int *y, int *x, bool reset)
{
	int static		pre_x;
	int static		pre_y;
	int static		manhdst;

	// if (enemy_ran_top(game, map))
	// {
	// 	game->hit_right = true;
	// 	game->hit_top = false;
	// }
	if (reset == 0)
		reset_values(&pre_x, &pre_y, &manhdst);
	if (game->stop_checking)
	{
		*x = pre_x;
		*y = pre_y;
		reset_values(&pre_x, &pre_y, &manhdst);
		if (map->max_x + 4 <= game->fig_max_x + *x)
		{
			game->hit_right = true;
			ft_dprintf(fd_test, "Hit target --> RIGHT WALL %d\n", game->fig_max_x);
			return (true);
		}
		ft_dprintf(fd_test, "Target --> RIGHT WALL\n");
		return (false);
	}
	if (manheten_dist(map->max_x, target_rw(map, map->enemy), *x, *y) <= manhdst)
	{
		ft_dprintf(fd_test, "Coord to check y%d x%d mnht %d\n",
		*y - y_cut_top, *x - x_cut_left - 4, manhdst);
		pre_x = *x;
		pre_y = *y;
		manhdst = manheten_dist(map->max_x, target_rw(map, map->enemy), *x, *y);
	}
	return (false);
}

bool	bottom(t_game *game, t_map *map, int *y, int *x, bool reset)
{
	int static		pre_x;
	int static		pre_y;
	int static		manh_dst;

	if (reset == 0)
		reset_values(&pre_x, &pre_y, &manh_dst);
	if (game->stop_checking)
	{
		*x = pre_x;
		*y = pre_y;
		reset_values(&pre_x, &pre_y, &manh_dst);
		if (map->max_y <= game->fig_max_y + *y)
		{
			game->hit_bottom = true;
			ft_dprintf(fd_test, "Hit target --> BOTTOM\n");
			return (true);
		}
		ft_dprintf(fd_test, "Target --> BOTTOM\n");
		return (false);
	}
	if (manheten_dist(map->max_y, target_bottom(map, map->enemy), *x, *y) <= manh_dst)
	{
		pre_x = *x;
		pre_y = *y;
		manh_dst = manheten_dist(map->max_y, target_bottom(map, map->enemy), *x, *y);
	}
	return (false);
}

bool	surround_enemy(t_game *game, t_map *map, int *y, int *x)
{
//				1				0						0				1
	// if ((!game->hit_right || !game->hit_left) && (!game->hit_top || !game->hit_bottom))
	// {
		if ((figure_view(game) == 'h' && !game->hit_right && !game->hit_left) ||
			(game->hit_top || game->hit_bottom))
		{
			// if (ENEMY_FROM_RIGHT)
			// {
				if (right_wall(game, map, y, x, game->reset))
					return (true);
			// }
			// else
			// 	if (left_wall(game, map, y, x, game->reset))
			// 		return (true);
		}
		else
		{
			if (ENEMY_FROM_BOTTOM)
			{
				if (bottom(game, map, y, x, game->reset))
					return (true);
			}
			else
			{
				if (top(game, map, y, x, game->reset))
					return (true);
			}
		}
//	}
	game->reset = (game->stop_checking) ? 0 : 1;
	// if (game->stop_checking)
	// 	game->reset = 0;
	// else
	// 	game->reset = 1;
	game->stop_checking = false;
	return (false);
}