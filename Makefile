# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: krioliin <krioliin@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2019/06/30 16:51:39 by krioliin       #+#    #+#                 #
#    Updated: 2019/08/14 13:53:18 by krioliin      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME			=	krioliin.filler
CFLAGS			=	-Wall -Wextra -Werror
LIB				=	libft/libft.a

FILES			=	main read_map find_spot additional_funcs\
					read_figure cut_figure clean_data \
					closest_to_enemy_pos surround_enemy \
					attack_top attack_bottom \
					attack_right attack_left

all: $(NAME)

$(NAME):
	@make -C libft/
	@clang -o $(NAME) $(addprefix src/, $(FILES:=.c)) -Iincludes/ $(LIB) $(CFLAGS)
	@echo "\033[0;32mCompiling Filler\033[0m"
clean:
	@rm -f libft/*.o
	@echo "\033[0;33mRemove object files\033[0m"
fclean: clean
	@rm -f $(NAME)
	@rm -f $(LIB)
	@echo "\033[0;33mRemove 'Filler' and 'libft.a'\033[0m"
re: fclean all
