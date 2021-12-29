CFLAGS = -Wall -Wextra -Werror -g3 #-fsanitize=address -fno-omit-frame-pointer

CC = clang

NAME = ms

SRC = $(wildcard *.c)

OBJ = $(SRC:%.c=%.o)

#.c.o:
#	$(CC) $(CFLAGS) -c $<

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -lreadline

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: clean fclean all

flemme: re
	make clean

.PHONY: clean fclean all re
