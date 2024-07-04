/*
** EPITECH PROJECT, 2024
** display_tuto
** File description:
** functions to display during the tuto's loop
*/

#include "game.h"

void display_tuto(dungeon_t *dungeon, display_t *display, entity_t *player,
    sprite_t *popup)
{
    animation_map_assets(dungeon);
    display_map(display, dungeon);
    sfRenderWindow_drawSprite(display->window, popup->sprite, NULL);
    player->rect = display_entity(display->window, player->clock,
        player->display[EXPLO_STATE], player->rect);
    sfRenderWindow_drawSprite(display->window,
        player->display[COMBAT_STATE]->sprite, NULL);
    sfRenderWindow_display(display->window);
    sfRenderWindow_clear(display->window, BG_DEFAULT_COLOR);
}
