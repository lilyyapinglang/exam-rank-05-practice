# 1. varaible
NAME = vect2
CXX = c++
CXXFLAGS =-Wall -Werror -Wextra -std=c++98 

SRC = main.cpp vect2.cpp
OBJ =$(SRC:.cpp=.o)

# 2.principle targets

all : $(NAME)

$(NAME):$(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(NAME)

#3. cleaning and reconstruct rules
clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

#4. protection
.PHONY: all clean fclean re 
