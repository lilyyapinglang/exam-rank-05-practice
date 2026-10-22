# name
NAME = polyset
CXX = c++
CXXFLAGS = -Wall -Werror -Wextra -std=c++98 -g

SRCS = main.cpp searchable_array_bag.cpp searchable_tree_bag.cpp set.cpp array_bag.cpp tree_bag.cpp 
OBJS = $(SRCS:.cpp=.o)

#rules
all : $(NAME)

$(NAME):$(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re 