/*
** EPITECH PROJECT, 2024
** B-MUL-200-PAR-2-1-myrpg-pierre.pruvost
** File description:
** fire_knight.c
*/

#include "combat.h"
#include "capacity.h"

void kf_fire_ball(combat_t *info, int self, int focus, cap_info_t *cap)
{
    if (info->field[focus] != NULL && info->field[focus]->status != DEAD) {
        attack_entity(info, focus, cap, -3);
    }
    info->field[self]->mod->atk += 1;
    cap->entity_hit[self] = 1;
    cap->type[self] = STAT_UP;
}

void kf_flame_blade(combat_t *info, int self, int focus, cap_info_t *cap)
{
    for (int i = NB_ENTITY_SQUAD; i < NB_ENTITY_SQUAD + 2; ++i) {
        if (info->field[i] != NULL && info->field[i]->status != DEAD) {
            attack_entity(info, i, cap, 0);
        }
    }
    cap->entity_hit[self] = 0 - info->field[self]->mod->atk;
    info->field[self]->mod->atk = 0;
    cap->type[self] = STAT_DOWN;
}

void kf_block(combat_t *info, int self, int focus, cap_info_t *cap)
{
    info->field[focus]->mod->pro += 8;
    cap->entity_hit[focus] = 8;
    cap->type[focus] = STAT_UP;
}
