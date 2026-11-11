NAME=bsq

CC = cc
#-g:保留行号信息,Valgrind 就会显示 main (main.c:23)。
#-O0:关闭优化,避免变量被优化掉导致行号对不上。
# -Wall -Wextra:编译器警告往往直接指出问题,
CFLAGS = -Wextra -Wall -Werror -g -O0

SRCS = main_dp.c
OBJS =$(SRCS:.c=.o)


all: $(NAME)

$(NAME):$(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re : fclean all

.PHNOY: all clean fclean re