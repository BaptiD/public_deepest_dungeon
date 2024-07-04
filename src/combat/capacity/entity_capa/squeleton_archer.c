/*
** EPITECH PROJECT, 2024
** B-MUL-200-PAR-2-1-myrpg-pierre.pruvost
** File description:
** sq_archer.c
*/

#include "combat.h"
#include "capacity.h"

void sqa_heavy_arrow(combat_t *info, int self, int focus, cap_info_t *cap)
{
    if (info->field[focus] != NULL && info->field[focus]->status != DEAD) {
        attack_entity(info, focus, cap, 1);
        bleed_entity(info->field[focus], 60, 2, 1);
    }
}

void sqa_dodge(combat_t *info, int self, int focus, cap_info_t *cap)
{
    info->field[self]->mod->spd += 1;
    info->field[self]->mod->crt += 5;
    cap->entity_hit[self] = 1;
    cap->type[self] = STAT_UP;
}

void sqa_double_arr(combat_t *info, int self, int focus, cap_info_t *cap)
{
    for (int i = 0; i < NB_ENTITY_SQUAD - 2; ++i) {
        if (info->field[i] != NULL && info->field[i]->status != DEAD) {
            attack_entity(info, i, cap, -1);
        }
    }
}
