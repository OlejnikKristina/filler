/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   surround_enemy.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: krioliin <krioliin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/28 17:49:50 by krioliin       #+#    #+#                */
/*   Updated: 2019/07/22 00:58:32 by krioliin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

void	figure_view(t_figure *figure, t_enemy *enemy)
{
	if (figure->cut_y <= ft_strlen(figure->cut_fig[0]))
		enemy->figure_view = 'v';
	else
		enemy->figure_view = 'h';
}

char	*choose_target(t_enemy *enemy, t_map *map, int *y, int *x)
{
	if (map->max_x / 2 <= enemy->square.x)
		return (ft_strdup("Right wall"));
	return (ft_strdup("Left wall"));
}

void	right_wall(t_enemy *enemy, t_map *map, int *y, int *x)
{
	int static		pre_x = 0;
	int static		pre_y = 0;

	if (pre_x <= *x && (pre_y <= *y && *y <= enemy->square.y))
	{
		pre_x = *x;
		pre_y = *y;
	}
	if (pre_x == 0 && pre_y == 0)
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
	ft_dprintf(fd_test, " RIGHT WALL\n");
}

void	left_wall(t_enemy *enemy, t_map *map, int *y, int *x)
{
	int static		pre_x = 0;
	int static		pre_y = 0;

	if (*x <= pre_x && (pre_y <= *y && *y <= enemy->square.y))
	{
		pre_x = *x;
		pre_y = *y;
	}
	if (pre_x == 0 && pre_y == 0)
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
	ft_dprintf(fd_test, " LEFT WALL\n");
}

void	botton(t_enemy *enemy, t_map *map, int *y, int *x)
{
	int static		pre_x = 0;
	int static		pre_y = 0;

	if (*y < pre_y)
	{
		pre_x = *x;
		pre_y = *y;
	}
	if (pre_x == 0 && pre_y == 0)
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
	ft_dprintf(fd_test, " BOTTON\n");
}

void	top(t_enemy *enemy, t_map *map, int *y, int *x)
{
	int static		pre_x = 0;
	int static		pre_y = 0;

	if (pre_y < *y)
	{
		pre_x = *x;
		pre_y = *y;
	}
	if (pre_x == 0 && pre_y == 0)
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
	char			*target;
	int static		pre_x = 0;
	int static		pre_y = 0;

	ft_dprintf(fd_test, "Surround enemy");
	if (enemy->figure_view == 'v')
	{
		//target = choose_target(enemy, map, y, x);
		if (map->max_x / 2 <= enemy->square.x)
			right_wall(enemy, map, y, x);
		else
			left_wall(enemy, map, y, x);
	}
	if (enemy->figure_view == 'h')
	{
		if (map->max_y / 2 <= enemy->square.y)
			botton(enemy, map, y, x);
		else
			top(enemy, map, y, x);
	}


	return (false);
}