# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rrhaenys <rrhaenys@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/11 13:06:44 by rrhaenys          #+#    #+#              #
#    Updated: 2019/01/10 03:20:42 by rrhaenys         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol
FLAGS = -Wall -Wextra -Werror
LIB = ./libft/libft.a
SRC_DIR = src/
SRC_FIL = $(shell ls src | grep -E "ft_.+\.c")
SRCS = $(addprefix  $(SRC_DIR), $(SRC_FIL))
OBJ	= $(SRCS:.c=.o)
INCLUDE =-Ilibft -Iminilibx_macos
MLX = -framework OpenCL -L./minilibx_macos -lmlx -framework OpenGL -framework AppKit
COMMAND = gcc

all: $(NAME)

$(NAME): $(LIB) $(OBJ)
	$(COMMAND) -o $(NAME) -g $(OBJ) $(LIB) $(INCLUDE) $(MLX)

$(LIB):
#	make -C ./minilibx_macos
	make -C ./libft

.c.o:
	$(COMMAND) $(FLAGS) $(INCLUDE) -g -c -o $@ $<

clean:
#	make -C ./minilibx_macos clean
	make -C ./libft clean
	/bin/rm -f $(OBJ)

fclean: clean
	make -C ./libft fclean
	/bin/rm -f $(NAME)

re: fclean all

.PHONY: clean fclean all re
