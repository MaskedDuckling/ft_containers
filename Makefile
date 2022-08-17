NAME = ft_containers

CC = c++

CFLAGS = -Wall -Wextra -Werror -std=c++98 
-fsanitize=address

SRC = main.cpp 

INC = vector.hpp

OBJ = $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ) $(INC)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

.cpp.o:
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

po: all clean
	./$(NAME)
re: fclean all

.PHONY: all re clean fclean
