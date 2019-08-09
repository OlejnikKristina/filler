/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   attack_top.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: krioliin <krioliin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/08/04 10:15:00 by krioliin       #+#    #+#                */
/*   Updated: 2019/08/09 17:50:54 by krioliin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

int		target_top_x(t_map *map, char enemy_chr, bool enemy_from_right)
{
	short		x;
	short		y;
	short		my_topest_open_spot;
	static bool		display_one;

	y = 0;
	x = map->max_x;
	while (4 <= x)
	{
		while (y < map->max_y)
		{
			if (map->map[y][x] == map->player)
			{
				if (display_one == 0)
				{
					ft_dprintf(fd_test, "topest open right spot y%d x%d\n", y, x);
					display_one = 1;
				}
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

bool	is_free_way_to_top(const int x, int y, char **map)
{
	while (0 <= y)
	{
		if (map[y][x] != '.')
			return (false);
		y--;
	}
	return (true);
}

// int		target_top_x(t_map *map, char enemy_chr, bool enemy_from_right)
// {
// 	int		y;
// 	int		x;

// 	y = 0;
// 	x = 0;
// 	while (y <= map->max_y)
// 	{
// 		if (findchr(map->map[y], map->player) != -1)
// 		{
// 			if (is_free_way_to_top(findchr(map->map[y], map->player), y, map->map))
// 				return (x);
// 		}
// 		y++;
// 	}
// 	return (-1);
// }

bool	top(t_game *game, t_map *map, int *y, int *x, bool reset)
{
	int static		pre_x = 0;
	int static		pre_y = 0;
	int static		manht_dst;

	if (reset == 0)
		reset_values(&pre_x, &pre_y, &manht_dst);
	if (game->stop_checking)
	{
		*x = pre_x;
		*y = pre_y;
		reset_values(&pre_x, &pre_y, &manht_dst);//If it will hit right wall
		if (*y - y_cut_top <= 0) //|| (map->max_x + 4 <= game->fig_max_x + (*x - 4)))
		{
			game->hit_top = true;
			ft_dprintf(fd_test, "Hit target --> TOP\n");
			return (true);
		}
		ft_dprintf(fd_test, "Target --> TOP Final Manht_Dst: %d\n", manht_dst);
		return (false);
	}
	if (manheten_dist(target_top_x(map, map->enemy, 1), 0, *x, *y) <= manht_dst)
	{
		pre_x = *x;
		pre_y = *y;
		manht_dst = manheten_dist(target_top_x(map, map->enemy, 1), 0, *x, *y);
	}
	return (false);
}
