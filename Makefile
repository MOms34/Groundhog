##
## EPITECH PROJECT, 2023
## epitech
## File description:
## momo
##

CXX        = g++ -std=c++20
NAME       = groundhog
TEST_NAME  = unit_tests
SRC_MAIN  = $(wildcard ./SRC/SRC_MAIN/*.cpp)

SRC			=	$(filter-out $(SRC_MAIN), $(wildcard ./SRC/*.cpp))

OBJ			=	$(SRC:.cpp=.o) \
				$(SRC_MAIN:.cpp=.o)
SRC_TESTS  = $(wildcard ./Tests/*.cpp)
CXXFLAGS   = -Werror -Wextra -Wall -g3
TFLAGS     = -lcriterion --coverage

.PHONY: all clean fclean re tests_run

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) -o $(NAME) $(OBJ) $(CXXFLAGS)

tests_run: fclean all
	mkdir -p Tests
	$(CXX) -o $(TEST_NAME) $(SRC) $(SRC_TESTS) $(TFLAGS) $(CXXFLAGS)
	./$(TEST_NAME)
	$(MAKE) clean

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME) $(TEST_NAME)
	$(RM) -r Tests
	find . -name '*.gcda' -delete
	find . -name '*.gcno' -delete

re: fclean all
