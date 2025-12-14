# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sblanco- <sblanco-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/25 17:28:54 by gade-oli          #+#    #+#              #
#    Updated: 2025/12/14 20:09:41 by sblanco-         ###   ########.fr        #
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
CFLAGS = -g #-fsanitize=address # -Wall -Wextra -Werror -g

INC = inc/cub3d.h inc/defines.h

SRC =	src/main.c \
		src/mlx/hooks.c src/mlx/window.c \
		src/core/init.c src/core/init_player.c \
		src/core/init_minimap_bonus.c \
		src/rendering/player_motion.c src/rendering/raycast.c src/rendering/texture.c \
		src/rendering/draw_bonus.c src/rendering/minimap_bonus.c \
		src/utils/ft_error.c src/utils/math.c src/utils/free_array.c

# PARSER
SRC += src/parser/texture_utils.c \
	src/parser/index.c

# VALIDATOR
SRC += src/validator/bfs_utils.c \
	src/validator/bfs.c \
	src/validator/utils.c \
	src/validator/index.c

OBJ = $(SRC:src/%.c=bin/%.o)

#lib-----------------------------------------------------------------------------

MLX_DIR = lib/MLX42
MLX_BUILD_DIR = $(MLX_DIR)/build
MLX = $(MLX_BUILD_DIR)/libmlx42.a
MLXFLAGS = -ldl -lglfw -pthread -lm

LIBFT_DIR = lib/megalibft/
LIBFT = $(LIBFT_DIR)megalibft.a

QUEUE_DIR = lib/queue/
QUEUE = $(QUEUE_DIR)libqueue.a

#recipes-------------------------------------------------------------------------

all: $(MLX) $(LIBFT) $(QUEUE) $(NAME)

$(LIBFT):
	@make --directory=$(LIBFT_DIR)
	@echo "$(GREEN)libft compiled!$(RESET)"

$(QUEUE):
	@make --directory=$(QUEUE_DIR)
	@echo "$(GREEN)queue compiled!$(RESET)"

$(MLX):
	@echo "$(BLUE)configuring MLX build and sources dirs on cmake$(RESET)"
	@cmake -B $(MLX_BUILD_DIR) -S $(MLX_DIR)
	@echo "$(BLUE)building MLX42$(RESET)"
	@cmake --build $(MLX_BUILD_DIR) -j4

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(QUEUE) $(LIBFT) $(MLX) $(MLXFLAGS) -o $(NAME)
	@echo "$(GREEN)cub3d compiled!$(RESET)"

bin/%.o: src/%.c $(INC)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ)
	@rm -rf $(MLX_BUILD_DIR)
	@make clean --directory=$(LIBFT_DIR)
	@make clean --directory=$(QUEUE_DIR)
	@echo "$(RED)binaries deleted!$(RESET)"

fclean: clean
	@make fclean --directory=$(LIBFT_DIR)
	@make fclean --directory=$(QUEUE_DIR)
	@rm -f $(NAME)
	@echo "$(RED)cub3d deleted!$(RESET)"

re: fclean all

.PHONY: all clean fclean re
