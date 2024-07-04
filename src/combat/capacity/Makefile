##
## EPITECH PROJECT, 2024
## B-MUL-200-PAR-2-1-myrpg-pierre.pruvost
## File description:
## MAKEFILE FOR CAPACITIES
##

SRC 	= 		./capa_interaction.c 						\
				./entity_capa/fire_knight.c 				\
				./effect_interaction.c						\
				./basics.c 									\
				./entity_capa/fire_wizard.c 				\
				./entity_capa/kunoichi.c 					\
				./entity_capa/lightning_mage.c 				\
				./entity_capa/ninja_monk.c 					\
				./entity_capa/ninja_peasant.c 				\
				./entity_capa/samurai_archer.c 				\
				./entity_capa/samurai_commander.c 			\
				./entity_capa/samurai.c 					\
				./entity_capa/squeleton_archer.c 			\
				./entity_capa/squeleton_warrior.c 			\
				./entity_capa/squeleton_spear.c	 			\
				./entity_capa/wizard_wanderer.c 			\
				./entity_capa/karasu_tengu.c 				\

## NORMAL COMPILATION OBJECTS
LIB	=	$(SRC:.c=.o)

## COMMON FLAGS
CPPFLAGS 	=	-I ../../../include
NAME_LIB	=	libcapa.a

## NORMAL MAIN COMPILATION
all:	init

init:	$(LIB)
	ar rc $(NAME_LIB) $(LIB)
	mv $(NAME_LIB) ../

re: fclean all

## CLEANING RULES
clean:
	rm -f $(LIB)

fclean:	clean
	rm -f ../$(NAME_LIB)

.PHONY: all init re clean fclean
