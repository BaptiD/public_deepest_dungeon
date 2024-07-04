/*
** EPITECH PROJECT, 2024
** tuto_loop
** File description:
** functions to manage tuto's loop
*/

#include "tuto.h"
#include "game.h"
#include "maps.h"
#include "entity.h"
#include "combat.h"
#include "sound.h"

void destroy_tuto(entity_t *player, dungeon_t *dungeon, sprite_t *popup)
{
    destroy_entities(player);
    sfTexture_destroy(popup->texture);
    sfSprite_destroy(popup->sprite);
    free(popup);
    destroy_dungeon(dungeon);
}

int tuto_loop(display_t *display)
{
    entity_t *player = setting_entity_from_file(FIRE_KNIGHT);
    dungeon_t *dungeon = init_tuto(player);
    pnj_t *pnj = dungeon->pnjs[0];
    sprite_t *popup = init_popup();
    int run_tuto = true;

    while (sfRenderWindow_isOpen(display->window) &&
        pnj->status_quest == NOT_DONE && run_tuto == true) {
        run_tuto = event_listener_tuto(display, player, dungeon, popup);
        display_tuto(dungeon, display, player, popup);
    }
    destroy_tuto(player, dungeon, popup);
    return run_tuto;
}
