# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iadrien <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/17 15:19:45 by iadrien           #+#    #+#              #
#    Updated: 2020/10/17 17:56:15 by iadrien          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

SRC = src/errors.c\
		src/color.c\
		src/draw.c\
		src/file.c\
		src/game.c\
		src/map.c\
		src/map1.c\
		src/move.c\
		src/parse.c\
		src/parse1.c\
		src/player.c\
		src/raycast.c\
		src/screensh.c\
		src/sprites.c\
		src/sprites1.c\
		src/texture.c\
		src/utils.c\
		src/utils1.c\
		src/main.c

INC = includes/cub3d.h \
		minilibx/mlx.h \
		includes/structs.h

OBJ = $(SRC:.c=.o)

LIB = -L. -lmlx
COMPILER_COMMAND = gcc
COMPILER_COMMAND_FLAGS = -Wall -Wextra -Werror
REMOVE_COMMAND = rm
REMOVE_COMMAND_FLAGS = -f

all: $(NAME)

$(NAME): $(OBJ) $(INC) libmlx.dylib
	$(COMPILER_COMMAND)  $(LIB) $(COMPILER_COMMAND_FLAGS) -Ofast -o $(NAME) $(OBJ)

libmlx.dylib:
	$(MAKE) -C minilibx/
	mv		minilibx/libmlx.dylib libmlx.dylib

bonus: all

mlx_clean:
	$(MAKE) -C minilibx/ clean

mlx_fclean: mlx_clean
	$(REMOVE_COMMAND) $(REMOVE_COMMAND_FLAGS) libmlx.dylib

clean: mlx_clean
	$(REMOVE_COMMAND) $(REMOVE_COMMAND_FLAGS) $(OBJ) $(BONUS_OBJ)

fclean: clean mlx_fclean
	$(REMOVE_COMMAND) $(REMOVE_COMMAND_FLAGS) $(NAME)

re: fclean all

.PHONY: OBJ BONUS_OBJ clean fclean all re