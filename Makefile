# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gade-oli <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/25 17:28:54 by gade-oli          #+#    #+#              #
#    Updated: 2025/11/14 21:13:39 by gade-oli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#colors-------------------------------------------------------------------------

RED     = \033[1;31m
GREEN   = \033[1;32m
BLUE    = \033[1;34m
RESET   = \033[0;0m

#variables----------------------------------------------------------------------

NAME = cub3d

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

INC = inc/cub3d.h inc/defines.h

SRC =	src/main.c \
	src/draw.c \
	src/utils/ft_error.c \
	src/utils/math.c \
	src/mlx/hooks.c

OBJ = $(SRC:src/%.c=bin/%.o)

#lib-----------------------------------------------------------------------------

MLX_DIR = lib/MLX42
MLX_BUILD_DIR = $(MLX_DIR)/build
MLX = $(MLX_BUILD_DIR)/libmlx42.a
MLXFLAGS = -ldl -lglfw -pthread -lm

LIBFT_DIR = lib/megalibft/
LIBFT = $(LIBFT_DIR)megalibft.a

#recipes-------------------------------------------------------------------------

all: $(MLX) $(LIBFT) $(NAME)
	@echo "$(GREEN)cub3d compiled!$(RESET)"

$(LIBFT):
	@make --directory=$(LIBFT_DIR)
	@echo "$(GREEN)libft compiled!$(RESET)"

$(MLX):
	@echo "$(BLUE)configuring MLX build and sources dirs on cmake$(RESET)"
	@cmake -B $(MLX_BUILD_DIR) -S $(MLX_DIR)
	@echo "$(BLUE)building MLX42$(RESET)"
	@cmake --build $(MLX_BUILD_DIR) -j4

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX) $(MLXFLAGS) -o $(NAME)

bin/%.o: src/%.c $(INC)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ)
	@rm -rf $(MLX_BUILD_DIR)
	@make clean --directory=$(LIBFT_DIR)
	@echo "$(RED)binaries deleted!$(RESET)"

fclean: clean
	@make fclean --directory=$(LIBFT_DIR)
	@rm -f $(NAME)
	@echo "$(RED)cub3d deleted!$(RESET)"

re: fclean all

.PHONY: all clean fclean re
