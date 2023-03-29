NAME = ft_containers

CC = c++

CFLAGS = -Wall -Wextra -Werror -std=c++98 -fsanitize=address

SRC = main.cpp 

INC =	vector.hpp \
		utils.hpp \
		stack.hpp \
		pair.hpp \
		vector_iterator.hpp \
		enable_if.hpp \
		equal.hpp \
		RB_tree.hpp \
		RB_node.hpp \
		is_integral.hpp \
		iterator_traits.hpp \
		reverse_iterator.hpp

INCS = ${addprefix headers/,${INC}}

OBJ = $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ) $(INCS)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

.cpp.o:
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all re clean fclean
