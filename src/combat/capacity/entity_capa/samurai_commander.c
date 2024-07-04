/*
** EPITECH PROJECT, 2024
** B-MUL-200-PAR-2-1-myrpg-pierre.pruvost
** File description:
** samurai_commander.c
*/

#include "combat.h"
#include "capacity.h"

void sc_basic(combat_t *info, int self, int focus, cap_info_t *cap)
{
    if (info->field[focus] != NULL && info->field[focus]->status != DEAD) {
        attack_entity(info, focus, cap, 0);
    }
}

void sc_motivation(combat_t *info, int self, int focus, cap_info_t *cap)
{
    for (int i = 0; i < NB_ENTITY_SQUAD; ++i) {
        if (info->field[i] != NULL && info->field[i]->status != DEAD) {
            info->field[i]->mod->crt += 2;
            cap->entity_hit[i] = 2;
            cap->type[i] = STAT_UP;
        }
    }
}

void sc_protect(combat_t *info, int self, int focus, cap_info_t *cap)
{
    for (int i = NB_ENTITY_SQUAD - 2; i < NB_ENTITY_SQUAD; ++i) {
        if (info->field[i] != NULL && info->field[i]->status != DEAD) {
            info->field[i]->mod->pro += 5;
            cap->entity_hit[i] = 5;
            cap->type[i] = STAT_UP;
        }
    }
}
