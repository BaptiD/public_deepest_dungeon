##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## compile my lib
##

## FILES SOURCES
SRC 	=	my/my_str_to_word_arr.c	\
			my/free_arr.c	\
			my/log_in_file.c \
			my/env_check.c \
			my/len_arr.c \
			my/get_file_in_arr.c \
			my/my_strdup.c 	\
			my/my_strlen.c	\
			my/my_strcmp.c	\
			my/clock_manage.c	\

## NORMAL COMPILATION OBJECTS
OBJ	=	$(SRC:.c=.o)

## COMMON FLAGS
CPPFLAGS 	=	-I ../../include
LIB	=	libmy.a

## NORMAL LIB COMPILATION
all:	init

init:	$(OBJ)
	ar rc $(LIB) $(OBJ)

re: fclean all

## CLEANING RULES
clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(LIB)

.PHONY: all init re clean fclean
