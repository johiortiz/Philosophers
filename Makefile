NAME = philo

CC = cc
CFLAGS = -Wall -Werror -Wextra -g
LIBS = -lpthread

SRCS = parsing.c \
	   utils.c \
	   init.c \
	   philosopher.c \
	   monitor.c \
	   main.c \
	   utils_philo.c

OBJS = $(SRCS:.c=.o)
HEADER = philo.h

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
