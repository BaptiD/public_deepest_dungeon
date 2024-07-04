/*
** EPITECH PROJECT, 2024
** B-MUL-200-PAR-2-1-myrpg-pierre.pruvost
** File description:
** capa_interaction.c
*/

#include "combat.h"
#include "capacity.h"

void monster_basic_attack(combat_t *info, int self, int focus, cap_info_t *cap)
{
    for (int i = NB_ENTITY_SQUAD - 1; i >= 0; --i) {
        if (info->field[i] != NULL && info->field[i]->status != DEAD) {
            attack_entity(info, i, cap, 0);
            return;
        }
    }
}

void ally_basic_attack(combat_t *info, int self, int focus, cap_info_t *cap)
{
    for (int i = 4; i < NB_ENTITY_SQUAD * 2; ++i) {
        if (info->field[i] != NULL && info->field[i]->status != DEAD) {
            attack_entity(info, i, cap, 0);
            return;
        }
    }
}

cap_info_t *launch_capacity(combat_t *info, int focus, int capacity_index,
    int capa_id)
{
    cap_info_t *cap = malloc(sizeof(cap_info_t));

    for (int i = 0; i < NB_ENTITY_SQUAD * 2; ++i) {
        cap->entity_hit[i] = IGNORE;
        cap->type[i] = IGNORE;
    }
    change_sprite_action(info->field[info->turn], capa_id);
    CAPACITY[capacity_index].func(info, info->turn, focus, cap);
    return cap;
}
