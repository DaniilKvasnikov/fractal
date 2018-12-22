# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rrhaenys <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/20 14:56:13 by rrhaenys          #+#    #+#              #
#    Updated: 2018/12/06 13:23:28 by rrhaenys         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
COMMAND = gcc
FLAGS = -Wall -Wextra -Werror -c -g
SRC		= $(shell ls | grep -E "ft_.+\.c")
OBJ		= $(SRC:.c=.o)
INCLUDE = ./

all: $(SRC) $(NAME)

$(NAME): $(OBJ) 
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

.c.o:
	$(COMMAND) $(FLAGS) -I $(INCLUDE) $< -o $@

clean:
	/bin/rm -f $(OBJ)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

.PHONY: clean fclean all re
