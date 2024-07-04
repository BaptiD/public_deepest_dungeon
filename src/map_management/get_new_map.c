/*
** EPITECH PROJECT, 2024
** B-MUL-200-PAR-2-1-myrpg-pierre.pruvost
** File description:
** get_new_map.c
*/

#include "game.h"
#include "my.h"

static void destroy_assets_in_map(map_display_t asset)
{
    if (asset.number <= 0)
        return;
    for (int i = 0; i < asset.number; ++i) {
        sfSprite_destroy(asset.display[i].sprite);
        sfTexture_destroy(asset.display[i].texture);
    }
    free(asset.display);
    free(asset.pos);
    free(asset.rect);
}

void destroy_map_display(dungeon_t *dungeon)
{
    sfSprite_destroy(dungeon->background.sprite);
    sfTexture_destroy(dungeon->background.texture);
    destroy_assets_in_map(dungeon->interaction);
    destroy_assets_in_map(dungeon->monster);
    destroy_assets_in_map(dungeon->pnj);
    destroy_assets_in_map(dungeon->assets);
}

static sfImage *set_square_background(char **map, int x, int y)
{
    if (map[y][x] == MAP_WALL)
        return sfImage_createFromFile(BG_FILEPATH_ASSETS[WALL]);
    return sfImage_createFromFile(BG_FILEPATH_ASSETS[ROCK_GROUND_1]);
}

static sfTexture *set_texture_from_map(char **map)
{
    sfTexture *texture = sfTexture_create(SIZE_MAP * ASSET_MAP_SIZE,
        SIZE_MAP * ASSET_MAP_SIZE);
    sfImage *image = NULL;

    for (int y = 0; y < SIZE_MAP; ++y) {
        for (int x = 0; x < SIZE_MAP; ++x) {
            image = set_square_background(map, x, y);
            sfTexture_updateFromImage(texture, image, x * ASSET_MAP_SIZE, y * ASSET_MAP_SIZE);
            sfImage_destroy(image);
        }
    }
    return texture;
}

static sprite_t setup_display_map_bg(char **map)
{
    sprite_t background = {0};
    sfVector2f ratio = {0, 0};

    background.sprite = sfSprite_create();
    background.texture = set_texture_from_map(map);
    sfSprite_setTexture(background.sprite, background.texture, sfTrue);
    ratio.x = MAP_SQUARE / ASSET_MAP_SIZE;
    ratio.y = MAP_SQUARE / ASSET_MAP_SIZE;
    sfSprite_setScale(background.sprite, ratio);
    return background;
}

void get_sprite_map(dungeon_t *dungeon, entity_t *player)
{
    char **map = ACTUAL_MAP.char_map;
    int i = 0;

    logs(INFO, "Setting new dungeon map...");
    dungeon->background = setup_display_map_bg(map);
    setup_map_assets(dungeon, map);
    logs(SUCCESS, "Map set OK");
    move_map(dungeon, (MAP_VISIBLE_X / 2) / MAP_SQUARE
        - player->pos[0], (MAP_VISIBLE_Y / 2) / MAP_SQUARE - player->pos[1]);
}
