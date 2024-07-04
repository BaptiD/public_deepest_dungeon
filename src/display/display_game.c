/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** display/display_game.c
*/

#include "game.h"

#include <stdio.h>

static void set_pos_up_down(char **map, entity_t *player, int pos)
{
    int y = 1;

    if (pos == DOWN)
        y = 18;
    for (size_t x = 1; x < 19; x++) {
        if (map[y + 1][x] == MAP_DOOR || map[y - 1][x] == MAP_DOOR) {
            player->pos[0] = x;
            player->pos[1] = y;
            return;
        }
    }
}

static void set_pos_side(char **map, entity_t *player, int pos)
{
    int x = 1;

    if (pos == RIGHT)
        x = 18;
    for (size_t y = 1; y < 19; y++) {
        if (map[y][x + 1] == MAP_DOOR || map[y][x - 1] == MAP_DOOR) {
            player->pos[0] = x;
            player->pos[1] = y;
            return;
        }
    }
}

static void change_coordinates(dungeon_t *dungeon, entity_t *player)
{
    switch (player->movement) {
        case LEFT:
            dungeon->co_map.x -= 1;
            set_pos_side(ACTUAL_MAP.char_map, player, RIGHT);
            break;
        case RIGHT:
            dungeon->co_map.x += 1;
            set_pos_side(ACTUAL_MAP.char_map, player, LEFT);
            break;
        case UP:
            dungeon->co_map.y -= 1;
            set_pos_up_down(ACTUAL_MAP.char_map, player, DOWN);
            break;
        case DOWN:
            dungeon->co_map.y += 1;
            set_pos_up_down(ACTUAL_MAP.char_map, player, UP);
            break;
    }
}

void change_map(dungeon_t *dungeon, entity_t *player)
{
    if (ACTUAL_MAP.char_map[player->pos[1]]
        [player->pos[0]] == MAP_DOOR) {
        if (dungeon->background.sprite != NULL) {
            destroy_map_display(dungeon);
        }
        change_coordinates(dungeon, player);
        get_sprite_map(dungeon, player);
        set_pnj_in_map(&ACTUAL_MAP, dungeon->pnjs, player);
    }
}

void main_display(dungeon_t *dungeon, entity_t *player, display_t *display)
{
    change_map(dungeon, player);
    display_map(display, dungeon);
    player->rect = display_entity(display->window, player->clock,
        player->display[EXPLO_STATE], player->rect);
    animation_map_assets(dungeon);
    sfRenderWindow_display(display->window);
    sfRenderWindow_clear(display->window, BG_DEFAULT_COLOR);
}
