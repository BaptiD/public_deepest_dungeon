/*
** EPITECH PROJECT, 2024
** B-MUL-200-PAR-2-1-myrpg-pierre.pruvost
** File description:
** display_map.c
*/

#include "game.h"

static void display_map_assets(display_t *display, map_display_t assets)
{
    for (int i = 0; i < assets.number; ++i) {
        sfRenderWindow_drawSprite(display->window,
            assets.display[i].sprite, NULL);
    }
}

void display_map(display_t *display, dungeon_t *dungeon)
{
    sfRenderWindow_drawSprite(display->window,
        dungeon->background.sprite, NULL);
    display_map_assets(display, dungeon->monster);
    display_map_assets(display, dungeon->interaction);
    display_map_assets(display, dungeon->pnj);
}
