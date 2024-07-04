/*
** EPITECH PROJECT, 2024
** B-MUL-200-PAR-2-1-myrpg-pierre.pruvost
** File description:
** squeleton_spear.c
*/

#include "combat.h"
#include "capacity.h"

void sqs_reach(combat_t *info, int self, int focus, cap_info_t *cap)
{
    if (info->field[focus] != NULL && info->field[focus]->status != DEAD) {
        attack_entity(info, focus, cap, 0);
    }
}

void sqs_break_gruard(combat_t *info, int self, int focus, cap_info_t *cap)
{
    if (info->field[focus] != NULL && info->field[focus]->status != DEAD) {
        info->field[focus]->mod->pro -= 10;
        cap->entity_hit[focus] = -10;
        cap->type[focus] = STAT_DOWN;
    }
}

void sqs_protect(combat_t *info, int self, int focus, cap_info_t *cap)
{
    info->field[self]->mod->pro += 5;
    cap->entity_hit[self] = 5;
    cap->type[self] = STAT_UP;
}
