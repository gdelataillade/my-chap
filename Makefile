##
## EPITECH PROJECT, 2017
## Makefile
## File description:
## Standard Makefile configuration
##

SRC =	src/main.c		\
		src/server.c	\
		src/error.c

OBJ =	$(SRC:.c=.o)

NAME =	client

GCC =	gcc

RM =	rm -f

CFLAGS =	-Wall -Wextra -I./include/ -g

all:	$(NAME)

$(NAME):	$(OBJ)
	$(GCC) -o $(NAME) $(OBJ) $(CFLAGS)
	@echo "Compilation du projet : My CHAP"

clean:
	$(RM) $(OBJ)

fclean:	clean
	$(RM) $(NAME)

re: fclean all
