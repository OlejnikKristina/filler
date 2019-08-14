/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   filler.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: krioliin <krioliin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/30 15:19:11 by krioliin       #+#    #+#                */
/*   Updated: 2019/08/14 14:14:55 by krioliin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H
# include "libft.h"
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdbool.h>
# define ENEMY_FROM_RIGHT (map->max_x / 2 <= game->square.x)
# define ENEMY_FROM_BOTTOM (map->max_y / 2 <= game->square.y)

typedef struct		s_map
{
	char			**map;
	int				max_x;
	int				max_y;
	char			player;
	char			enemy;
}					t_map;

typedef struct		s_figure
{
	char			**field;
	char			**cut_fig;
	int				cut_y;
	int				cut_x;
	int				size_x;
	int				size_y;
}					t_figure;

typedef struct		s_coord
{
	int				x;
	int				y;
}					t_coord;

typedef struct		s_game
{
	t_coord			square;
	char			figure_view;
	int				fig_max_x;
	int				fig_max_y;
	bool			stop_checking;
	bool			hit_bottom;
	bool			hit_top;
	bool			hit_left;
	bool			hit_right;
	bool			reset;
}					t_game;

/*
** ************************** Attack *********************************
*/

int					target_rw(t_map *map, t_game *game, char enemy_chr);
int					target_bottom(t_map *map, char game_chr);
int					manhtn_dist(int i, int j, int x, int y);
void				reset_values(int *pre_x, int *pre_y, int *manh_dst);
bool				check_spot(t_map *map, int y, int x, t_figure *fig);
bool				surround_enemy(t_game *game, t_map *map, int *y, int *x);
bool				top(t_game *game, t_map *map, int *yx[2], bool reset);
bool				bottom(t_game *game, t_map *map, int *yx[2], bool reset);
bool				left_wall(t_game *game, t_map *map, int *yx[2], bool reset);
bool				right_wall(t_game *game, t_map *map, int *yx[2],
					bool reset);
bool				closest_to_enemy_pos(t_game *game, t_map *map,
					int *y, int *x);

/*
** ********************** Process figure* *****************************
*/

char				figure_view(t_game *game);
void				read_figure(t_figure *figure, t_game *game);
void				cut_figure(t_figure *figure);
int					cut_y_top(t_figure *figure);
short unsigned		cut_x_left(t_figure *figure);
short unsigned		cut_x_right(t_figure *figure);

/*
** ********************** Find coordinats ******************************
*/

bool				read_map(t_map *map);
void				find_possible_spot(t_map *map, t_figure *figure,
					t_game *game);
/*
** ********************** Addtional functions ********************************
*/

void				clean_data(t_map *map, t_figure *figure);
bool				ret_set(bool *set);
void				increment(int *increment_me, int *add_plus_one);
short				max_y_filed(t_map *map, char **cut_figure);
void				set_to_null(int	*set_me_null, int *and_me,
					bool *me_as_well);

#endif
