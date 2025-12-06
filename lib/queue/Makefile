NAME = libqueue.a

RM = /bin/rm -f

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g

INC = -I. -I../megalibft

SRC = ft_queue_init.c \
      ft_enqueue.c \
      ft_dequeue.c

OBJS = ${SRC:%.c=bin/%.o}

all: ${NAME}

bin/%.o: %.c queue.h
	@mkdir -p bin
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

${NAME}: ${OBJS}
	ar -rcs ${NAME} ${OBJS}

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re

