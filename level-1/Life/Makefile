NAME =a.out

CC = cc
CFLAGS =-Wall -Wextra -Werror -g #-0

SRCS =main.c
OBJS =$(SRCS:.c=.o)

all:$(NAME)

$(NAME):$(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm rf $(OBJS)

fclean:clean
	rm rf $(NAME)

re: fclean all

.PHONY: all clean fclean re