/*
** EPITECH PROJECT, 2024
** B-MUL-200-PAR-2-1-myrpg-pierre.pruvost
** File description:
** karasu_tengu.c
*/

#include "combat.h"
#include "capacity.h"

void kt_bleeder(combat_t *info, int self, int focus, cap_info_t *cap)
{
    attack_entity(info, focus, cap, +2);
}

void kt_slash(combat_t *info, int self, int focus, cap_info_t *cap)
{
    for (int i = 0; i < NB_ENTITY_SQUAD; ++i) {
        if (info->field[i] != NULL && info->field[i]->status != DEAD) {
            attack_entity(info, i, cap, -2);
        }
    }
}

void kt_crow_eye(combat_t *info, int self, int focus, cap_info_t *cap)
{
    info->field[self]->mod->crt += 5;
    info->field[self]->mod->pre += 5;
    cap->entity_hit[self] = 5;
    cap->type[self] = STAT_UP;
}
