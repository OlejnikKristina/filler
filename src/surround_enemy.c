/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   surround_enemy.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: krioliin <krioliin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/28 17:49:50 by krioliin       #+#    #+#                */
/*   Updated: 2019/07/30 19:48:30 by krioliin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"
//if (*x <= pre_x && (pre_y <= *y && *y <= enemy->square.y))
//if (pre_x <= *x) //&& (pre_y - 2 <= *y && *y <= enemy->square.y + 5))
//if (pre_y <= *y) BOTTOM
void	figure_view(t_figure *figure, t_enemy *enemy)
{
	if (figure->cut_y <= ft_strlen(figure->cut_fig[0]) - 1)
		enemy->figure_view = 'h';
	else
		enemy->figure_view = 'v';
}
// from vm spot				y18;x21;
// from test map spot		y16;x20;
// mine choosen best spot	y20;x15

int		target_rw(t_map *map, char enemy_chr)
{
	int		y;

	y = 0;
	while (y < map->max_y)
	{
		if (ft_strchr(map->map[y], enemy_chr))
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

int		mnhtn_rw(int i, int j, int x, int y)
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

void	left_wall(t_enemy *enemy, t_map *map, int *y, int *x)
{
	int static		pre_x = 0;
	int static		pre_y = 0;

	if (enemy->stop_checking)
	{
		*x = pre_x;
		*y = pre_y;
		pre_x = 0;
		pre_y = 0;
	}
	if (pre_x <= *x && (pre_y <= *y))// && *y <= enemy->square.y + 5))
	{
		pre_x = *x;
		pre_y = *y;
	}
	ft_dprintf(fd_test, " LEFT WALL\n");
}

int		target_bottom(t_map *map, char enemy_chr)
{
	int		x;
	int		y;
	bool	enemy_right;

	y = 0;
	x = 4;
	while (x < map->max_x + 4)
	{
		while (y < map->max_y)
		{
			if (map->map[y][x] == enemy_chr)
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

int		target_top(t_map *map, char enemy_chr, bool enemy_from_right)
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
				return (0);
			}
			if (map->map[y][x] == enemy_chr)
				break ;
			y++;
		}
		x--;
		y = 0;
	}
	return (0);
}

void	right_wall(t_enemy *enemy, t_map *map, int *y, int *x)
{
	short static		pre_x;
	short static		pre_y;
	short static		manhdst;

	if (enemy->stop_checking)
	{
		*x = pre_x;
		*y = pre_y;
		pre_x = 0;
		pre_y = 0;
		if (enemy->fig_max_x <= *x + enemy->fig_max_x)
			enemy->hit_right = true;
		ft_dprintf(fd_test, "Target --> RIGHT WALL\n");
	}
	if (pre_x == 0 && pre_y == 0)
		manhdst = mnhtn_rw(map->max_x, target_rw(map, map->enemy), *x, *y);
	if (mnhtn_rw(map->max_x, target_rw(map, map->enemy), *x, *y) <= manhdst)
	{
		pre_x = *x;
		pre_y = *y;
		manhdst = mnhtn_rw(map->max_x, target_rw(map, map->enemy), *x, *y);
	}
}

void	bottom(t_enemy *enemy, t_map *map, int *y, int *x)
{
	int static		pre_x;
	int static		pre_y;
	int static		manhdst;

	if (enemy->stop_checking)
	{
		*x = pre_x;
		*y = pre_y;
		pre_x = 0;
		pre_y = 0;
		if (enemy->fig_max_y + *y == map->max_y)
		{
			enemy->hit_bottom = true;
			return ;
		}
		ft_dprintf(fd_test, "Target --> BOTTOM Final ManhDst: %d\n", manhdst);
	}
	if (pre_x == 0 && pre_y == 0)
		manhdst = mnhtn_rw(map->max_y, target_bottom(map, map->enemy), *x, *y);
	if (mnhtn_rw(map->max_y, target_bottom(map, map->enemy), *x, *y) <= manhdst)
	{
		pre_x = *x;
		pre_y = *y;
		manhdst = mnhtn_rw(map->max_y, target_bottom(map, map->enemy), *x, *y);
	}
}

void	top(t_enemy *enemy, t_map *map, int *y, int *x)
{
	int static		pre_x = 0;
	int static		pre_y = 0;

	if (*y <= pre_y)
	{
		pre_x = *x;
		pre_y = *y;
	}
	if (enemy->stop_checking)
	{
		*x = pre_x;
		*y = pre_y;
		pre_x = 0;
		pre_y = 0;
	}
	ft_dprintf(fd_test, " TOP\n");
}

bool	surround_enemy(t_enemy *enemy, t_map *map, int *y, int *x)
{
	//target_top(map, map->enemy, 0);
	if ((enemy->figure_view == 'h' && !enemy->hit_right) || enemy->hit_bottom)
	{
	//	if (map->max_x / 2 <= enemy->square.x)
			right_wall(enemy, map, y, x);
	// 	else
	// 		left_wall(enemy, map, y, x);
	}
	else if (enemy->figure_view == 'v' || enemy->hit_right)
	{
	//	if (map->max_y / 2 <= enemy->square.y)
			bottom(enemy, map, y, x);
	// 	else
	//		top(enemy, map, y, x);
	}
	return (false);
}