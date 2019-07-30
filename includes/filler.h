/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   filler.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: krioliin <krioliin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/30 15:19:11 by krioliin       #+#    #+#                */
/*   Updated: 2019/07/30 18:21:16 by krioliin      ########   odam.nl         */
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

int					fd_test;

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

typedef struct		s_enemy
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
	bool			surround_enemy;
	bool			hit_bottom;
	bool			hit_top;
	bool			hit_left;
	bool			hit_right;
}					t_enemy;

/*
** ************************** Attack *********************************
*/

void				solver(t_map *map, t_enemy *enemy, t_figure *figure);
void				closest_enemy_pos(t_enemy *enemy, t_map *map);
bool				surround_enemy(t_enemy *enemy, t_map *map, int *y, int *x);

void				figure_view(t_figure *figure, t_enemy *enemy);
bool				read_map(t_map *map);
void				add_spot(t_spot **spot_top, int y, int x);

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
					t_enemy *enemy);
int					max_x_filed(t_map *map, char *figure);
short				max_y_filed(t_map *map, char **figure);

/*
** ********************** Clean data ************************************
*/

void				clean_data(t_map *map, t_figure *figure, t_enemy *enemy);
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
