/*
** EPITECH PROJECT, 2024
** B-MUL-200-PAR-2-1-myrpg-pierre.pruvost
** File description:
** squeletton_warrior.c
*/

#include "combat.h"
#include "capacity.h"

void sqw_breaker(combat_t *info, int self, int focus, cap_info_t *cap)
{
    if (info->field[focus] != NULL && info->field[focus]->status != DEAD) {
        attack_entity(info, focus, cap, -1);
        stun_entity(info->field[focus], 50);
    }
}

void sqw_bleeder(combat_t *info, int self, int focus, cap_info_t *cap)
{
    if (info->field[focus] != NULL && info->field[focus]->status != DEAD) {
        attack_entity(info, focus, cap, -1);
        bleed_entity(info->field[focus], 70, 2, 2);
    }
}

void sqw_protect(combat_t *info, int self, int focus, cap_info_t *cap)
{
    info->field[self]->mod->pro += 10;
    cap->entity_hit[self] = 10;
    cap->type[self] = STAT_UP;
}
