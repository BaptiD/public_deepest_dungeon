##
## EPITECH PROJECT, 2024
## makefile
## File description:
## COMBAT MAKEFILE
##

## FILES SOURCES

SRC	=			./main_loop.c 										\
				./create_monster_squad.c 							\
				./combat_arrival.c 									\
				./xp_gain.c 										\
				./close_combat.c 									\
				./combat_info.c 									\
				./setup_combat.c 									\
				./event/main_event.c 								\
				./event/capacity_event.c 							\
				./event/turn_management.c							\
				./displays/display_combat.c 						\
				./displays/display_damages.c 						\
				./displays/display_hp_bar.c 						\
				./displays/display_xp_combat.c 						\
				./displays/display_stats.c 							\
				./displays/display_capacities.c 					\
				./effect_loop/effect_loop.c 						\
				./effect_loop/do_effect.c							\
				./animation/combat_animation.c 						\
				./animation/impact_frame.c 							\
				./animation/death.c									\

## NORMAL COMPILATION OBJECTS
OBJ	=	$(SRC:.c=.o)

## COMMON FLAGS
CPPFLAGS 	=	-I ../../include
LIBS	=	-L./capacity -lcapa
LIB	=	libcombat.a

## NORMAL MAIN COMPILATION
all:	init

init:	$(OBJ)
	$(MAKE) -C ./capacity -j
	ar rc $(LIB) $(OBJ)

re: fclean all

## CLEANING RULES
clean:
	$(MAKE) clean -C ./capacity
	rm -f $(OBJ)

fclean:	clean
	$(MAKE) fclean -C ./capacity
	rm -f $(LIB)

.PHONY: all init re clean fclean
