/*
** EPITECH PROJECT, 2024
** B-MUL-200-PAR-2-1-myrpg-pierre.pruvost
** File description:
** animation_map.c
*/

#include "maps.h"

static void move_asset_rect(map_display_t asset)
{
    sfIntRect rect;

    for (int i = 0; i < asset.number; ++i) {
        rect = asset.rect[i];
        rect.left += 32;
        if (rect.left >= 128)
            rect.left = 0;
        sfSprite_setTextureRect(asset.display[i].sprite, rect);
        asset.rect[i] = rect;
    }
}

void animation_map_assets(dungeon_t *dungeon)
{
    if (time_elapsed(dungeon->clock->time, MAP_ASSET_ANIMATION_SPEED
         * dungeon->clock->index) == sfTrue) {
        move_asset_rect(dungeon->monster);
        move_asset_rect(dungeon->pnj);
        dungeon->clock->index += 1;
    }
    if (time_elapsed(dungeon->clock->time, 5.0) == sfTrue) {
        sfClock_restart(dungeon->clock->time);
        dungeon->clock->index = 0;
    }
}
