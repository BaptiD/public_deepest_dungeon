/*
** EPITECH PROJECT, 2024
** B-MUL-200-PAR-2-1-myrpg-pierre.pruvost
** File description:
** lightning_mage.c
*/

#include "combat.h"
#include "capacity.h"

void lm_blind_spark(combat_t *info, int self, int focus, cap_info_t *cap)
{
    for (int i = NB_ENTITY_SQUAD; i < NB_ENTITY_SQUAD + 2; ++i) {
        if (info->field[i] != NULL && info->field[i]->status != DEAD) {
            info->field[i]->mod->pre -= 4;
            cap->entity_hit[i] = -4;
            cap->type[i] = STAT_DOWN;
        }
    }
}

void lm_light_ball(combat_t *info, int self, int focus, cap_info_t *cap)
{
    for (int i = NB_ENTITY_SQUAD; i < NB_ENTITY_SQUAD * 2; ++i) {
        if (info->field[i] != NULL && info->field[i]->status != DEAD) {
            attack_entity(info, i, cap, -2);
        }
    }
}

void lm_paralyze(combat_t *info, int self, int focus, cap_info_t *cap)
{
    for (int i = 4; i < NB_ENTITY_SQUAD + 2; ++i) {
        if (info->field[i] != NULL && info->field[i]->status != DEAD) {
            attack_entity(info, i, cap, -3);
            info->field[i]->mod->spd -= 1;
        }
    }
}
