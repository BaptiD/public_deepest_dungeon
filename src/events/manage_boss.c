/*
** EPITECH PROJECT, 2024
** pnj
** File description:
** functions to manage_boss
*/

#include <stdio.h>
#include <stdbool.h>

#include "entity.h"
#include "game.h"
#include "combat.h"
#include "my.h"

sfBool next_to_boss(dungeon_t *dungeon, entity_t *player, int x, int y)
{
    if (player->pos[1] + y >= 0 && player->pos[1] + y <= 19 &&
        player->pos[0] + x >= 0 && player->pos[0] + x <= 19) {
        if (ACTUAL_MAP.char_map[player->pos[1] + y][player->pos[0] + x]
            == MAP_BOSS) {
            ACTUAL_MAP.char_map[player->pos[1] + y][player->pos[0] + x] = ' ';
            return sfTrue;
        }
    }
    return sfFalse;
}

sfBool is_close_to_boss(dungeon_t *dungeon, entity_t *player)
{
    if (next_to_boss(dungeon, player, -1, -1) == sfTrue)
        return sfTrue;
    if (next_to_boss(dungeon, player, -1, 0) == sfTrue)
        return sfTrue;
    if (next_to_boss(dungeon, player, -1, 1) == sfTrue)
        return sfTrue;
    if (next_to_boss(dungeon, player, 0, -1) == sfTrue)
        return sfTrue;
    if (next_to_boss(dungeon, player, 0, 1) == sfTrue)
        return sfTrue;
    if (next_to_boss(dungeon, player, 1, -1) == sfTrue)
        return sfTrue;
    if (next_to_boss(dungeon, player, 1, 0) == sfTrue)
        return sfTrue;
    if (next_to_boss(dungeon, player, 1, 1) == sfTrue)
        return sfTrue;
    return sfFalse;
}

void manage_boss(dungeon_t *dungeon, entity_t *player, display_t *display, int *run_game)
{
    if (is_close_to_boss(dungeon, player) == sfTrue) {
        combat_loop(display, player, BOSS_KARASU, run_game);
        if (is_alive(player) == sfTrue) {
            dungeon->floor++;
            get_sprite_map(dungeon, player);
        }
    }
}
