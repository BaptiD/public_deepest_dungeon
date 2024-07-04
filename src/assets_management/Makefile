##
## EPITECH PROJECT, 2024
## makefile
## File description:
## COMBAT MAKEFILE
##

## FILES SOURCES

SRC	= 	./sprites/init.c						\
		./sprites/destroy.c						\
		./sprites/get_rect.c					\
		./sound/manage_struct.c 				\
		./sound/play_sound.c 					\
		./entity/setting_entity.c 				\
		./entity/set_entity_stats.c				\
		./entity/clear_entity.c 				\
		./entity/set_display_entity.c 			\
		./entity/add_entity_to_squad.c 			\
		./entity/move_entity_in_squad.c 		\
		./entity/lvl_up.c 						\
		./entity/pnjs/pnj.c						\
		./entity/pnjs/init_pnjs.c 				\
		./entity/pnjs/add_pnj_to_squad.c   		\
		./entity/pnjs/pnj_utils.c   			\

## NORMAL COMPILATION OBJECTS
OBJ	=	$(SRC:.c=.o)

## COMMON FLAGS
CPPFLAGS 	=	-I ../../include
LIB	=	libassets.a

## NORMAL MAIN COMPILATION
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
