SRC	=	src/Main.cpp				\
		src/Core.cpp				\
		src/Data.cpp				\
		src/Doodle.cpp				\
		src/Platform.cpp			\
		src/Boost.cpp				\
		src/Score.cpp				\

OBJ = 	$(SRC:.cpp=.o)

NAME = 	DoodleJump

CXXFLAGS = -std=c++17 -Wall -Wextra -Weffc++

CPPFLAGS = -iquote include

CXX = g++

LDLIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

all :	$(OBJ)
	$(CXX) -o $(NAME) $(OBJ) $(LDLIBS)

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re: fclean all