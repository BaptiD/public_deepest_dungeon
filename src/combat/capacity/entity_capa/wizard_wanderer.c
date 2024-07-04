/*
** EPITECH PROJECT, 2024
** B-MUL-200-PAR-2-1-myrpg-pierre.pruvost
** File description:
** wizard_wanderer.c
*/
#include "combat.h"
#include "capacity.h"

void ww_smoke_screen(combat_t *info, int self, int focus, cap_info_t *cap)
{
    if (info->field[focus] == NULL)
        return;
    info->field[focus]->mod->pre -= 8;
    cap->entity_hit[focus] = -8;
    cap->type[focus] = STAT_DOWN;
}

void ww_air_speed(combat_t *info, int self, int focus, cap_info_t *cap)
{
    for (int i = 0; i < NB_ENTITY_SQUAD; ++i) {
        if (info->field[i] != NULL && info->field[i]->status != DEAD) {
            info->field[i]->mod->spd += 1;
            cap->entity_hit[i] = 1;
            cap->type[i] = STAT_UP;
        }
    }
}

void ww_wind_slash(combat_t *info, int self, int focus, cap_info_t *cap)
{
    int damages_harved =
        (info->field[self]->stats->atk + info->field[self]->mod->atk) / 2;

    for (int i = NB_ENTITY_SQUAD; i < NB_ENTITY_SQUAD * 2; ++i) {
        if (info->field[i] != NULL && info->field[i]->status != DEAD) {
            attack_entity(info, i, cap, -(damages_harved));
        }
    }
}
