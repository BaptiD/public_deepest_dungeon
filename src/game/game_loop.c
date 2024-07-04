/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** game/gameloop.c
*/

#include "game.h"
#include "sprites.h"
#include "statics.h"
#include "my.h"

int game(display_t *display, entity_t *player, dungeon_t *dungeon)
{
    int run_game = true;

    get_sprite_map(dungeon, player);
    if (!display->window || dungeon == NULL)
        return 84;
    while (sfRenderWindow_isOpen(display->window) && run_game == true) {
        event_listener(display, player, dungeon, &run_game);
        run_game = end_of_game(player, dungeon, run_game);
        if (run_game == true)
            main_display(dungeon, player, display);
    }
    sfMusic_stop(display->sounds[BG_MUSIC_WAV]);
    sfMusic_stop(display->sounds[COMBAT_MUSIC_WAV]);
    destroy_dungeon(dungeon);
    return save_game_in_file(dungeon, player);
}
