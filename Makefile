NAME = cub3d
SRCS = main.c 
OBJS=$(SRCS:.c=.o)
READLINE_PATH = vendor/readline
LIBFT = ./libft
LIBFT_NAME = libft.a

# Compiler stuff
CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g3
INCLUDES = -I $(LIBFT) #-I $(READLINE_PATH)/include
LNK = -L $(LIBFT) -lft -lreadline #-L $(READLINE_PATH)/lib  -lreadline

all: $(LIBFT_NAME) $(NAME)

clean:
	rm -f $(OBJS)
	make clean -C $(LIBFT)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFT)

re: fclean all

%.o: %.c
	$(CC) $(INCLUDES) $(CFLAGS) -c $< -o $@

# Libft include
$(LIBFT_NAME):
	make bonus -C $(LIBFT) $(LIBFT_NAME)

$(NAME):  $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LNK)
.PHONY: make re fclean clean all