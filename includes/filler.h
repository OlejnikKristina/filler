/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   filler.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: krioliin <krioliin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/30 15:19:11 by krioliin       #+#    #+#                */
/*   Updated: 2019/08/09 17:51:02 by krioliin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H
# include "../libft/includes/libft.h"
# include "../libft/includes/get_next_line.h"
#include "ft_printf.h"
#include "ftpf_colors.h"
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdbool.h>
# include <errno.h>
# define PRINT false
# define ENEMY_FROM_RIGHT map->max_x / 2 <= game->square.x
# define ENEMY_FROM_BOTTOM map->max_y / 2 <= game->square.y

int					fd_test;
int					y_cut_top;
int					x_cut_left;

typedef struct		s_map
{
	char			**old_map;
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
	int				size_x;
	int				size_y;
}					t_figure;

typedef	struct		s_spot
{
	int				y;
	int				x;
	char			position;
	struct s_spot	*next;
}					t_spot;

typedef struct		s_coord
{
	int				x;
	int				y;
}					t_coord;

/*
**
** left = left extreme coordinate;
** right = right exreme coordinate;
**
*/

typedef struct		s_game
{
	t_coord			left;
	t_coord			right;
	t_coord			square;
	t_coord			my;
	char			*target_hit;
	char			figure_view;

	int				fig_max_x;
	int				fig_max_y;

	bool			stop_checking;

	char			*target;
	bool			surround_game;
	bool			hit_bottom;
	bool			hit_top;
	bool			hit_left;
	bool			hit_right;
	bool			reset;
}					t_game;

/*
** ************************** Attack *********************************
*/

void				solver(t_map *map, t_game *game, t_figure *figure);
void				closest_enemy_pos(t_game *game, t_map *map);
bool				surround_enemy(t_game *game, t_map *map, int *y, int *x);
bool				top(t_game *game, t_map *map, int *y, int *x, bool reset);
bool				bottom(t_game *game, t_map *map, int *y, int *x, bool reset);
bool				left_wall(t_game *game, t_map *map, int *y, int *x, bool reset);
bool				right_wall(t_game *game, t_map *map, int *y, int *x, bool reset);

int					target_rw(t_map *map, char enemy_chr);//right-left wall
int					target_bottom(t_map *map, char game_chr);//top-bottom

bool				b(t_game *game, t_map *map, int *y, int *x);
bool				block_enemy(t_game *game, t_map *map, int *y, int *x, bool reset);
int					manheten_dist(int i, int j, int x, int y);

char				figure_view(t_game *game);
void				reset_values(int *pre_x, int *pre_y, int *manh_dst);

void				reset_values(int *pre_x, int *pre_y, int *manh_dst);
char				figure_view(t_game *game);
bool				read_map(t_map *map);
void				add_spot(t_spot **spot_top, int y, int x);
void				save_old_map(t_map *map);

/*
** ********************** Process figure* *****************************
*/

void				read_figure(t_figure *figure);
void				cut_figure(t_figure *figure);
void				figure_del(t_figure *figure);
int					cut_y_top(t_figure *figure);
short unsigned		cut_x_left(t_figure *figure);
short unsigned		cut_x_right(t_figure *figure);

/*
** ********************** Find coordinats ******************************
*/

void				find_possible_spot(t_map *map, t_figure *figure,
					t_game *game);
int					max_x_filed(t_map *map, char *figure);
short				max_y_filed(t_map *map, char **figure);

/*
** ********************** Clean data ************************************
*/

void				clean_data(t_map *map, t_figure *figure, t_game *game);
void				free_arr(void ***arr, size_t i);
void				field_del(char **str, int size);
void				map_del(t_map *map);
void				spot_del(t_spot **node);

/*
** ********************** Test functions ********************************
*/

void				map_print(t_map *map);

#define TEST_FILE "/Users/krioliin/Desktop/second_filler/filler_krioliin/src/test_file.txt"
#define TEST_MAP "/Users/krioliin/Desktop/second_filler/filler_krioliin/src/test_map.txt"

#endif
