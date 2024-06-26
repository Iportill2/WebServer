NAME = webserver
CPP = c++
CFLAGS = -Wall -Werror -Wextra #-std=c++98 #-g3 -fsanitize=address
SRC_FILES = main.cpp \
			Server.cpp \
			Request.cpp \
			Response.cpp \
			Error.cpp \
			Utils.cpp \
			Config.cpp  \
			Location.cpp \
			srv.cpp 

OBJS = $(SRC_FILES:.cpp=.o)

all: $(NAME)

%.o: %.cpp
	$(CPP) -c $(CFLAGS)  $^

$(NAME): $(OBJS)
	$(CPP) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re