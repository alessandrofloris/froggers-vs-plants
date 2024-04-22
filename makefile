CC = cc
SHELL = /bin/sh
CFLAGS += -Iinclude -Wall -Werror -Wextra -Wno-error=unused-result
LDFLAGS += -lncurses -ltinfo
PREFIX = /usr/local

NAME = froggers

SRCS:= $(shell find -name "*.c")

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LDFLAGS)

.o: .c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	find . -name "*.o" -delete -print

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)

debug: CFLAGS += -g
debug: fclean $(NAME)

.PHONY: all clean fclean re install uninstall debug