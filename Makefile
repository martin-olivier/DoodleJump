SRC	=	src/main.cpp				\
		src/Sound.cpp				\
		src/Engine.cpp				\
		src/Doodle.cpp				\

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