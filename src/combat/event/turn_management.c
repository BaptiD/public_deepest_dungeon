/*
** EPITECH PROJECT, 2024
** B-MUL-200-PAR-2-1-myrpg-pierre.pruvost
** File description:
** turn.c
*/

#include "my.h"
#include "combat.h"

static int find_fastest(combat_t *info)
{
    int highest_spd = 0;
    int index = -1;

    for (int i = 0; i < NB_ENTITY_SQUAD * 2; ++i) {
        if (info->field[i] != NULL && info->field[i]->stats->spd +
            info->field[i]->mod->spd > highest_spd &&
            info->played[i] == WAIT && info->field[i]->status != DEAD) {
            index = i;
            highest_spd = info->field[i]->stats->spd +
                info->field[i]->mod->spd;
        }
    }
    return index;
}

void next_turn(display_t *display, combat_t *info)
{
    int highest_spd = 0;
    int index = -1;

    if (info->turn != -1)
        info->played[info->turn] = PLAYED;
    index = find_fastest(info);
    if (index == -1) {
        for (int i = 0; i < NB_ENTITY_SQUAD * 2; ++i)
            info->played[i] = 0;
        index = find_fastest(info);
    }
    logs(INFO, "Next turn...");
    info->turn = index;
    effect_manage(display, info);
}
