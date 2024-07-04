/*
** EPITECH PROJECT, 2024
** B-MUL-200-PAR-2-1-myrpg-pierre.pruvost
** File description:
** fire_wizard.c
*/

#include "combat.h"
#include "capacity.h"

void fw_back_slash(combat_t *info, int self, int focus, cap_info_t *cap)
{
    for (int i = 7; i >= NB_ENTITY_SQUAD; --i) {
        if (info->field[i] != NULL && info->field[i]->status != DEAD) {
            attack_entity(info, i, cap, 0);
            return;
        }
    }
}

void fw_fire_ball(combat_t *info, int self, int focus, cap_info_t *cap)
{
    for (int i = 7; i >= NB_ENTITY_SQUAD + 2; --i) {
        if (info->field[i] != NULL && info->field[i]->status != DEAD) {
            attack_entity(info, i, cap, -2);
            burn_entity(info->field[i], 60, 2, 2);
        }
    }
}

void fw_flame_throw(combat_t *info, int self, int focus, cap_info_t *cap)
{
    for (int i = 4; i < NB_ENTITY_SQUAD + 2; ++i) {
        if (info->field[i] != NULL && info->field[i]->status != DEAD) {
            attack_entity(info, i, cap, -2);
            info->field[i]->mod->pre -= 2;
        }
    }
}
