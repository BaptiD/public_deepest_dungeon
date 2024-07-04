/*
** EPITECH PROJECT, 2024
** B-MUL-200-PAR-2-1-myrpg-pierre.pruvost
** File description:
** move_map.c
*/

#include "maps.h"

static void move_assets(map_display_t assets, double x, double y)
{
    sfVector2f pos;

    if (assets.number <= 0)
        return;
    for (int i = 0; i < assets.number; ++i) {
        pos = sfSprite_getPosition(assets.display[i].sprite);
        assets.pos[i] = pos;
        sfSprite_setPosition(assets.display[i].sprite,
            (sfVector2f){x * MAP_SQUARE + pos.x, y * MAP_SQUARE + pos.y});
    }
}

void move_map(dungeon_t *dungeon, double x, double y)
{
    sfVector2f pos = sfSprite_getPosition(dungeon->background.sprite);

    sfSprite_setPosition(dungeon->background.sprite,
        (sfVector2f){x * MAP_SQUARE + pos.x, y * MAP_SQUARE + pos.y});
    move_assets(dungeon->monster, x, y);
    move_assets(dungeon->pnj, x, y);
    move_assets(dungeon->interaction, x, y);
    move_assets(dungeon->assets, x, y);
}
