# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: popanase <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/09 14:26:53 by popanase          #+#    #+#              #
#    Updated: 2018/07/17 14:57:16 by popanase         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in

SRC = main.c parse.c validate.c routes_handler.c links_handler.c free.c \
	  finish_routes.c print_result.c dfs_0.c bfs_0.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	make -C libft
	make -C ft_printf
	gcc -Wall -Wextra -Werror $^ -L./libft -lft -L./ft_printf -lftprintf -o $@
	
%.o: %.c
	gcc -Wall -Wextra -Werror -c $<

clean: 
	make clean -C libft
	make clean -C ft_printf
	rm -f $(OBJ)

fclean: clean 
	make fclean -C libft
	make fclean -C ft_printf
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
