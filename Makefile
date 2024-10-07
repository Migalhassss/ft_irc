# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: micarrel <micarrel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/01 13:54:38 by micarrel          #+#    #+#              #
#    Updated: 2024/10/01 13:54:38 by micarrel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	IRCServer
CXX	=	c++

CXXFLAGS	=	-Wall	-Wextra	-Werror	-g	-std=c++98

FILES	=	main.cpp		\
			Server.cpp		\
			Client.cpp		\
			Commands.cpp	
OBJ	=	$(FILES:.cpp=.o)

all:	$(NAME) $(OBJ)

$(NAME):	$(OBJ)
	$(CXX)	$(CXXFLAGS)	$(FILES)	-o	$(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm	-f $(NAME)

re:	fclean	all