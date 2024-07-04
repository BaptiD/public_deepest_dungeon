/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** gaming boiiiii
*/

#include "game.h"
#include "my.h"

bool end_of_game(entity_t *player, dungeon_t *dungeon, int run_game)
{
    if (player->stats->hp + player->mod->hp <= 0) {
        return false;
    }
    if (dungeon->floor > BOSS_TO_WIN) {
        return false;
    }
    return run_game;
}
