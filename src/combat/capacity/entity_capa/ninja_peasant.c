/*
** EPITECH PROJECT, 2024
** B-MUL-200-PAR-2-1-myrpg-pierre.pruvost
** File description:
** ninja_peasant.c
*/

#include "combat.h"
#include "capacity.h"

void np_knif(combat_t *info, int self, int focus, cap_info_t *cap)
{
    if (info->field[focus] != NULL && info->field[focus]->status != DEAD) {
        attack_entity(info, focus, cap, 0);
    }
}

void np_bunker(combat_t *info, int self, int focus, cap_info_t *cap)
{
    info->field[self]->mod->crt += 2;
    info->field[self]->mod->pro += 5;
    cap->entity_hit[self] = 2;
    cap->type[self] = STAT_UP;
}

void np_dart(combat_t *info, int self, int focus, cap_info_t *cap)
{
    if (info->field[focus] != NULL && info->field[focus]->status != DEAD) {
        attack_entity(info, focus, cap, 1);
        poison_entity(info->field[focus], 70, 2, 1);
    }
}
