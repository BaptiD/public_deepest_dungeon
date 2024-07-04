/*
** EPITECH PROJECT, 2024
** events_tuto
** File description:
** functions to mangage events during tuto
*/

#include "game.h"
#include "combat.h"
#include "sprites.h"
#include "tuto.h"

static int manage_keyboard_click(display_t *display,
    entity_t *player, dungeon_t *dungeon)
{
    maps_t map = ACTUAL_MAP;
    pnj_t *pnj = dungeon->pnjs[0];
    int run_game = true;

    if (sfKeyboard_isKeyPressed(sfKeyEscape))
        pause_menu(display, &run_game);
    if (run_game == false)
        return false;
    move_key(player, display, dungeon);
    if (is_combat_start(dungeon, player) == sfTrue) {
        add_pnj_to_squad(player, pnj);
        combat_loop_tuto(display, player, NO_BOSS, pnj);
        pnj->status_quest = DONE;
    }
    return true;
}

int event_listener_tuto(display_t *display, entity_t *player,
    dungeon_t *dungeon, sprite_t *popup)
{
    int run_tuto = true;
    sfEvent event;
    pnj_t *pnj = dungeon->pnjs[0];

    while (sfRenderWindow_pollEvent(display->window, &event)) {
        if (event.type == sfEvtClosed)
            sfRenderWindow_close(display->window);
        if (event.type == sfEvtKeyPressed && !sfKeyboard_isKeyPressed(sfKeyE))
            run_tuto = manage_keyboard_click(display, player, dungeon);
        if (run_tuto == false)
            return false;
        manage_pnj_tuto(dungeon, player, display, popup);
    }
    return run_tuto;
}
