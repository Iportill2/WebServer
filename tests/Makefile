# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++11 -Wall -Wextra -Werror

# Name of the executable
NAME = tester2

# Source files
SRCS = tester2.cpp \
       test_get.cpp \
       test_post.cpp \
       test_delete.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Header files
HEADERS = tester2.hpp \
          test_get.hpp \
          test_post.hpp \
          test_delete.hpp

# Default target
all: $(NAME)

# Rule to create the executable
$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Rule to compile source files
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean object files
clean:
	rm -f $(OBJS)

# Clean object files and executable
fclean: clean
	rm -f $(NAME)

# Rebuild everything
re: fclean all

# Run the program
run: $(NAME)
	./$(NAME)

# Phony targets
.PHONY: all clean fclean re run