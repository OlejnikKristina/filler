# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: krioliin <krioliin@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2019/06/30 16:51:39 by krioliin       #+#    #+#                 #
#    Updated: 2019/08/13 11:06:43 by krioliin      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME			=	krioliin.filler
CFLAGS			=	-Wall -Wextra -Werror
LIB				=	libft/libft.a

FILES			=	main.c read_map.c find_spot.c additional_funcs.c\
					read_figure.c cut_figure.c clean_data.c \
					closest_to_enemy_pos.c surround_enemy.c \
					attack_top.c attack_bottom.c \
					attack_right.c attack_left.c
all: $(NAME)

$(NAME):
	@make -C libft/
	@clang -o $(NAME) $(addprefix src/, $(FILES)) -Iincludes/ $(LIB) $(CFLAGS)
	@echo "\033[0;32mCompiling Filler\033[0m"
clean:
	@rm -f libft/*.o
	@echo "\033[0;33mRemove object files\033[0m"
fclean: clean
	@rm -f $(NAME)
	@rm -f $(LIB)
	@echo "\033[0;33mRemove 'Filler' and 'libft.a'\033[0m"
re: fclean all
