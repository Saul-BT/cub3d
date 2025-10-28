# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gade-oli <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/25 17:28:54 by gade-oli          #+#    #+#              #
#    Updated: 2025/10/28 21:59:16 by gade-oli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#colors-------------------------------------------------------------------------

#colors----------------------------------------------------------

RED     = \033[1;31m
GREEN   = \033[1;32m
BLUE    = \033[1;34m
RESET   = \033[0;0m

#variables----------------------------------------------------------------------

NAME = cub3d

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

SRC = src/main.c
OBJ = $(SRC:.c=.o)

MLX_DIR = lib/MLX42
MLX_BUILD_DIR = $(MLX_DIR)/build
MLX = $(MLX_BUILD_DIR)/libmlx42.a
MLXFLAGS = -ldl -lglfw -pthread -lm

#recipes-------------------------------------------------------------------------

all: $(MLX) $(NAME)

$(MLX):
	@echo "$(BLUE)configuting MLX build and sources directories on cmake$(RESET)"
	@cmake -B $(MLX_BUILD_DIR) -S $(MLX_DIR)
	@echo "$(BLUE)building MLX42$(RESET)"
	@cmake --build $(MLX_BUILD_DIR) -j4

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(MLX) $(MLXFLAGS) -o $(NAME)

bin/%.o: src/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -I$(MLX_DIR) -c $< -o $@

clean:
	rm -f $(OBJ)
	@echo "$(RED)clean MLX42 objects$(RESET)"
	rm -rf $(MLX_BUILD_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
