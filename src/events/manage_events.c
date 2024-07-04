/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** events/manage_events.c
*/

#include "game.h"
#include "combat.h"
#include "sprites.h"
#include "items.h"

static void manage_keyboard_click(display_t *display, entity_t *player,
    dungeon_t *dungeon, int *run_game)
{
    maps_t map = ACTUAL_MAP;

    if (sfKeyboard_isKeyPressed(sfKeyEscape))
        pause_menu(display, run_game);
    if (sfKeyboard_isKeyPressed(sfKeyTab)) {
        usleep(100000);
        inventory(display, player);
    }
    move_key(player, display, dungeon);
    if (is_combat_start(dungeon, player) == sfTrue) {
        sfMusic_pause(display->sounds[BG_MUSIC_WAV]);
        combat_loop(display, player, NO_BOSS, run_game);
        get_an_item(display, player, ITEM_COMBAT_CHANCE);
        sfMusic_play(display->sounds[BG_MUSIC_WAV]);
        get_sprite_map(dungeon, player);
    }
}

static void manage_mouse_click(display_t *display)
{
    sfVector2i pos = sfMouse_getPositionRenderWindow(display->window);
}

void event_listener(display_t *display, entity_t *player, dungeon_t *dungeon,
    int *run_game)
{
    sfEvent event;

    while (sfRenderWindow_pollEvent(display->window, &event)) {
        if (event.type == sfEvtClosed)
            sfRenderWindow_close(display->window);
        if (event.type == sfEvtMouseButtonPressed)
            manage_mouse_click(display);
        if (event.type == sfEvtKeyPressed) {
            manage_keyboard_click(display, player, dungeon, run_game);
            manage_pnj(dungeon, player, display, run_game);
            manage_heal(dungeon, player, display);
            manage_chest(dungeon, player, display);
            manage_boss(dungeon, player, display, run_game);
        }
    }
}
