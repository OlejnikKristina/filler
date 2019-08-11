# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: krioliin <krioliin@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2019/06/30 16:51:39 by krioliin       #+#    #+#                 #
#    Updated: 2019/08/11 19:02:57 by krioliin      ########   odam.nl          #
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
					closest_to_enemy_pos.c surround_enemy.c \
					attack_top.c attack_bottom.c \
					attack_right.c attack_left.c
all: $(NAME)

$(NAME):
	clang -o $(NAME) -g $(FILES) -I./includes/ $(LIB)
test:
	./filler_vm -p1 filler_krioliin/src/krioliin.filler \
	-p2 players/carli.filler -f maps/map01

fclean:
	rm -f $(NAME)

re: fclean all