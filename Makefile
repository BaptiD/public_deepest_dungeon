##
## EPITECH PROJECT, 2024
## makefile
## File description:
## noice
##

## FILES SOURCES
MAIN	=	main.c	\

SRC_PATH 	=	./src
SRC	=	$(SRC_PATH)/game/launcher.c											\
		$(SRC_PATH)/game/init_game.c 										\
		$(SRC_PATH)/game/game_loop.c										\
		$(SRC_PATH)/game/destroy_dungeon.c									\
		$(SRC_PATH)/game/create_dungeons.c									\
		$(SRC_PATH)/game/create_rooms.c										\
		$(SRC_PATH)/game/lobby.c											\
		$(SRC_PATH)/game/check_end_game.c									\
		$(SRC_PATH)/display/display_game.c									\
		$(SRC_PATH)/display/display_entities.c								\
		$(SRC_PATH)/display/display_map.c 									\
		$(SRC_PATH)/display/animation_map.c 								\
		$(SRC_PATH)/events/manage_events.c									\
		$(SRC_PATH)/events/manage_player_moves.c							\
		$(SRC_PATH)/events/manage_heal.c									\
		$(SRC_PATH)/events/manage_chests.c									\
		$(SRC_PATH)/events/manage_boss.c									\
		$(SRC_PATH)/map_management/get_map_from_file.c 						\
		$(SRC_PATH)/map_management/setup_map_assets.c 						\
		$(SRC_PATH)/map_management/move_map.c 								\
		$(SRC_PATH)/map_management/setup_dungeon.c 							\
		$(SRC_PATH)/map_management/links_maps.c 							\
		$(SRC_PATH)/map_management/get_new_map.c 							\
		$(SRC_PATH)/menus/options/loop.c									\
		$(SRC_PATH)/menus/options/events.c									\
		$(SRC_PATH)/menus/options/drag_n_drop_music.c						\
		$(SRC_PATH)/menus/options/drag_n_drop_effects.c						\
		$(SRC_PATH)/menus/options/display.c									\
		$(SRC_PATH)/menus/popups/confirm_popup.c							\
		$(SRC_PATH)/menus/popups/upgrade_popup.c							\
		$(SRC_PATH)/menus/popups/chest/chest_waiting.c						\
		$(SRC_PATH)/menus/popups/chest/chest_opening.c						\
		$(SRC_PATH)/menus/popups/chest/chest_obtained.c						\
		$(SRC_PATH)/menus/inventory/loop.c									\
		$(SRC_PATH)/menus/inventory/manage_clicks.c							\
		$(SRC_PATH)/menus/inventory/display/display.c						\
		$(SRC_PATH)/menus/inventory/display/display_squad.c					\
		$(SRC_PATH)/menus/inventory/display/display_buttons.c				\
		$(SRC_PATH)/menus/inventory/display/display_selection.c				\
		$(SRC_PATH)/menus/inventory/display/display_items.c					\
		$(SRC_PATH)/menus/inventory/display/display_stats.c					\
		$(SRC_PATH)/menus/inventory/display/display_part_stats.c			\
		$(SRC_PATH)/menus/inventory/drag_n_drop_member.c					\
		$(SRC_PATH)/menus/inventory/drag_n_drop_item.c						\
		$(SRC_PATH)/menus/inventory/remove_stuff.c							\
		$(SRC_PATH)/menus/hero_selection.c									\
		$(SRC_PATH)/menus/pause.c											\
		$(SRC_PATH)/menus/init_menu_sprites.c								\
		$(SRC_PATH)/menus/help.c											\
		$(SRC_PATH)/menus/saves/load_save.c 								\
		$(SRC_PATH)/menus/saves/save_game.c 								\
		$(SRC_PATH)/utils.c													\
		$(SRC_PATH)/tuto/init_tuto.c 										\
		$(SRC_PATH)/tuto/tuto_loop.c 										\
		$(SRC_PATH)/tuto/events_tuto.c 										\
		$(SRC_PATH)/tuto/display_tuto.c 									\
		$(SRC_PATH)/tuto/manage_dialogue.c 									\
		$(SRC_PATH)/tuto/combat_tuto.c 										\

## NORMAL COMPILATION OBJECTS
OBJ	=	$(SRC:.c=.o) $(MAIN:.c=.o)
NAME	=	my_rpg

## COMMON FLAGS
CSFML_CPL	=	-lcsfml-graphics -lcsfml-window -lcsfml-system -lcsfml-audio
CPPFLAGS =	-I include

## LIBS
MY_LIBS	=	-L$(SRC_PATH)/mylib -lmy
COMBAT_LIBS	=	-L$(SRC_PATH)/combat -lcombat -lcapa
ASSET_LIBS	=	-L$(SRC_PATH)/assets_management -lassets
LDLIBS 	=	 $(COMBAT_LIBS) $(ASSET_LIBS) $(CSFML_CPL) $(MY_LIBS) -lm

## UNIT-TESTS OBJECTS
TESTS   =       -lcriterion --coverage
TEST_NAME =     unit_tests
I 	=	$(CPPFLAGS)
TESTS_FILES =   tests/test.c

## NORMAL MAIN COMPILATION
all: $(NAME)

$(NAME):	$(OBJ)
		$(MAKE) -C $(SRC_PATH)/mylib -j
		$(MAKE) -C $(SRC_PATH)/assets_management -j
		$(MAKE) -C $(SRC_PATH)/combat -j
		gcc -o $(NAME) $(OBJ) $(LDLIBS)

re:     fclean all

## DEBUG FLAG FOR VALGRIND
debug: CPPFLAGS += -g3
debug: re

## UNIT-TESTS COMPILATION
tests_run: CPPFLAGS += --coverage
tests_run: fclean
	$(MAKE) -C $(SRC_PATH)/mylib -j
	$(MAKE) -C $(SRC_PATH)/assets_management -j
	$(MAKE) -C $(SRC_PATH)/combat -j
	$(CC) -o $(TEST_NAME) $(TESTS_FILES) $(SRC) $(LDLIBS) $(TESTS) $(I)
	./$(TEST_NAME)

## CLEANING RULES
clean:
	$(MAKE) clean -C $(SRC_PATH)/combat
	$(MAKE) clean -C $(SRC_PATH)/assets_management
	$(MAKE) clean -C $(SRC_PATH)/mylib
	$(RM) -f *.gcno *.gcda
	$(RM) $(OBJ)

fclean: clean
	$(MAKE) fclean -C $(SRC_PATH)/combat
	$(MAKE) fclean -C $(SRC_PATH)/assets_management
	$(MAKE) fclean -C $(SRC_PATH)/mylib
	$(RM) $(TEST_NAME) rpg.log
	$(RM) $(NAME)

.PHONY: all re debug tests_run clean fclean
