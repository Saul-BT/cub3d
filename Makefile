NAME = cub3d
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
SRC = src/main.c
OBJ = $(SRC:.c=.o)

#todo: build the mlx on compile time with the cub3d
MLX = libs/MLX42/build/libmlx42.a
MLXFLAGS = -ldl -lglfw -pthread -lm

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(MLXFLAGS) $(CFLAGS) $(OBJ) $(MLX) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
