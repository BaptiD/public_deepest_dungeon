/*
** EPITECH PROJECT, 2024
** B-MUL-200-PAR-2-1-myrpg-pierre.pruvost
** File description:
** setup_map_assets.c
*/

#include "maps.h"

static void is_asset(char square, dungeon_t *dungeon)
{
    if (square == MAP_PNJ)
        dungeon->pnj.number += 1;
    if (square == MAP_CHEST || square == MAP_HEAL)
        dungeon->interaction.number += 1;
    if (square == MAP_MONSTER || square == MAP_BOSS)
        dungeon->monster.number += 1;
}

static void count_assets_in_map(dungeon_t *dungeon, char **map)
{
    dungeon->pnj.number = 0;
    dungeon->monster.number = 0;
    dungeon->interaction.number = 0;
    dungeon->assets.number = 0;
    for (int y = 0; y < SIZE_MAP; ++y) {
        for (int x = 0; x < SIZE_MAP; ++x) {
            is_asset(map[y][x], dungeon);
        }
    }
}

static void malloc_map_display(map_display_t *display)
{
    display->index = 0;
    if (display->number > 0) {
        display->display = malloc(sizeof(sprite_t) * display->number);
        display->pos = malloc(sizeof(sfVector2f) * display->number);
        display->rect = malloc(sizeof(sfIntRect) * display->number);
    }
}

static void set_entity(map_display_t *asset, int x, int y, int id)
{
    sfVector2f ratio;

    asset->pos[asset->index].x = x * MAP_SQUARE;
    asset->pos[asset->index].y = y * MAP_SQUARE;
    asset->display[asset->index].sprite = sfSprite_create();
    asset->display[asset->index].texture = sfTexture_createFromFile(
        BG_FILEPATH_ASSETS[id], NULL);
    asset->rect[asset->index] = (sfIntRect){0, 0, 32, 32};
    sfSprite_setTexture(asset->display[asset->index].sprite,
        asset->display[asset->index].texture, sfTrue);
    sfSprite_setTextureRect(asset->display[asset->index].sprite,
        asset->rect[asset->index]);
    sfSprite_setPosition(asset->display[asset->index].sprite,
        asset->pos[asset->index]);
    ratio.x = MAP_SQUARE / BG_SIZE_ASSETS[id].x;
    ratio.y = MAP_SQUARE / BG_SIZE_ASSETS[id].y;
    sfSprite_setScale(asset->display[asset->index].sprite, ratio);
    asset->index += 1;
}

static void set_asset(map_display_t *asset, int x, int y, int id)
{
    sfVector2f ratio;

    asset->pos[asset->index].x = x * MAP_SQUARE;
    asset->pos[asset->index].y = y * MAP_SQUARE;
    asset->display[asset->index].sprite = sfSprite_create();
    asset->display[asset->index].texture = sfTexture_createFromFile(
        BG_FILEPATH_ASSETS[id], NULL);
    sfSprite_setTexture(asset->display[asset->index].sprite,
        asset->display[asset->index].texture, sfTrue);
    sfSprite_setPosition(asset->display[asset->index].sprite,
        asset->pos[asset->index]);
    ratio.x = MAP_SQUARE / BG_SIZE_ASSETS[id].x;
    ratio.y = MAP_SQUARE / BG_SIZE_ASSETS[id].y;
    sfSprite_setScale(asset->display[asset->index].sprite, ratio);
    asset->index += 1;
}

static void setup_map_display(dungeon_t *dungeon, char **map, int x, int y)
{
    if (map[y][x] == MAP_MONSTER)
        set_entity(&dungeon->monster, x, y, MONSTER);
    if (map[y][x] == MAP_PNJ)
        set_entity(&dungeon->pnj, x, y, PNJ);
    if (map[y][x] == MAP_CHEST)
        set_asset(&dungeon->interaction, x, y, CHEST);
    if (map[y][x] == MAP_HEAL)
        set_asset(&dungeon->interaction, x, y, FOUNTAIN);
}

void setup_map_assets(dungeon_t *dungeon, char **map)
{
    count_assets_in_map(dungeon, map);
    malloc_map_display(&dungeon->pnj);
    malloc_map_display(&dungeon->assets);
    malloc_map_display(&dungeon->monster);
    malloc_map_display(&dungeon->interaction);
    for (int y = 0; y < SIZE_MAP; ++y) {
        for (int x = 0; x < SIZE_MAP; ++x) {
            setup_map_display(dungeon, map, x, y);
        }
    }
}
