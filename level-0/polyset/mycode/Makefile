SRCS = main.cpp array_bag.cpp searchable_array_bag.cpp searchable_tree_bag.cpp set.cpp tree_bag.cpp
INCLUDES = array_bag.hpp bag.hpp searchable_array_bag.hpp searchable_bag.hpp searchable_tree_bag.hpp set.hpp tree_bag.hpp 
CC = c++
CFLAGS = -Wall -Werror -Wextra -std=c++98 -g

OBJ_DIR = obj
OBJS = ${SRCS:%.cpp=$(OBJ_DIR)/%.o}

NAME = polyset

all: $(NAME)

$(OBJ_DIR)/%.o: %.cpp $(INCLUDES)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -rf $(OBJ_DIR)
	
fclean: clean
	rm -f $(NAME)

re: fclean all

test: re
	python test.py

.PHONY: all clean fclean re