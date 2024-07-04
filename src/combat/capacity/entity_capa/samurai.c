/*
** EPITECH PROJECT, 2024
** B-MUL-200-PAR-2-1-myrpg-pierre.pruvost
** File description:
** samurai.c
*/

#include "combat.h"
#include "capacity.h"

void s_heavy_hit(combat_t *info, int self, int focus, cap_info_t *cap)
{
    if (info->field[focus] != NULL && info->field[focus]->status != DEAD) {
        attack_entity(info, focus, cap, 2);
    }
}

void s_blind(combat_t *info, int self, int focus, cap_info_t *cap)
{
    if (info->field[focus] != NULL && info->field[focus]->status != DEAD) {
        attack_entity(info, focus, cap, -2);
        info->field[focus]->mod->pre -= 2;
    }
}

void s_protect(combat_t *info, int self, int focus, cap_info_t *cap)
{
    info->field[self]->mod->pro += 8;
    cap->entity_hit[self] = 8;
    cap->type[self] = STAT_UP;
}
