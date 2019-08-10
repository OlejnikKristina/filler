# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: krioliin <krioliin@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2019/06/30 16:51:39 by krioliin       #+#    #+#                 #
#    Updated: 2019/08/10 18:13:33 by krioliin      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME			=	krioliin.filler
CFLAGS			=	-Wall -Wextra -Werror
LIB				=	../libft/libft.a \
					../libft/libftprintf.a

INCLUDES		=	../includes/filler.h \
					../includes/ft_pirntf.h \
					../includes/ftpf_colors.h \
					../includes/libft.h

FILES			=	main.c read_map.c find_spot.c \
					read_figure.c cut_figure.c clean_data.c \
					print_map.c closest_enemy_pos.c solver.c \
					max_xy_field.c add_node.c surround_enemy.c \
					block_enemy.c save_old_map.c attack_top.c \
					attack_bottom.c attack_right_wall.c \
					attack_left_wall.c check_priority_spots.c
all: $(NAME)

$(NAME):
	clang -o $(NAME) -g $(FILES) -I./includes/ $(LIB)
test:
	./filler_vm -p1 filler_krioliin/src/krioliin.filler \
	-p2 players/carli.filler -f maps/map01

fclean:
	rm -f $(NAME)

re: fclean all