##
## Makefile for epitech in /home/chapui_s/rendu/
##
## Made by chapui_s
## Login   <chapui_s@epitech.eu>
##
## Started on  Tue Nov 10 21:42:16 2015 chapui_s
## Last update Tue Nov 10 21:42:16 2015 chapui_s
##

NAME			= server

SRC			= src/main.cpp

OBJ			= $(SRC:.cpp=.o)

INCLUDES		= -I ./includes

CC			= clang++

RM			= rm -f

override CXXFLAGS	+= -std=c++11 -Wall -Wextra $(INCLUDES)

DEPS			= $(OBJ:.o=.d)

$(NAME):	$(OBJ)
		$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJ) $(LDLIBS)

-include $(DEPS)

all:		$(NAME)

%.o:		%.cpp
		$(CXX) -c $(CXXFLAGS) -MMD -MF $(patsubst %.o,%.d,$@) -c -o $@ $<

clean:
		$(RM) $(OBJ)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all

.PHONY:		all clean fclean re
