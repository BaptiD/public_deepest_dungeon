/*
** EPITECH PROJECT, 2024
** B-MUL-200-PAR-2-1-myrpg-pierre.pruvost
** File description:
** kunoichi.c
*/

#include "combat.h"
#include "capacity.h"

void k_slow(combat_t *info, int self, int focus, cap_info_t *cap)
{
    if (info->field[focus] != NULL && info->field[focus]->status != DEAD) {
        attack_entity(info, focus, cap, -2);
        info->field[focus]->mod->spd -= 2;
    }
}

void k_heal(combat_t *info, int self, int focus, cap_info_t *cap)
{
    int heal = arc4random() % (1 - (-1) + 1) + (-1);

    if (info->field[focus] == NULL && info->field[focus]->status == DEAD)
        return;
    if (crit_chance(info->field[self]) == sfTrue) {
        heal += 5 * CRIT_RATIO;
        cap->type[focus] = HEAL_CRIT;
    } else {
        heal += 5;
        cap->type[focus] = HEAL;
    }
    info->field[focus]->mod->hp += heal;
    if (info->field[focus]->mod->hp > 0) {
        heal = heal - info->field[focus]->mod->hp;
        info->field[focus]->mod->hp = 0;
    }
    cap->entity_hit[focus] = heal;
}

static void heal_entity(combat_t *info, int self, int i, cap_info_t *cap)
{
    int heal = arc4random() % (1 - (-1) + 1) + (-1);

    if (crit_chance(info->field[self]) == sfTrue) {
        heal += 3 * CRIT_RATIO;
        cap->type[i] = HEAL_CRIT;
    } else {
        heal += 3;
        cap->type[i] = HEAL;
    }
    info->field[i]->mod->hp += heal;
    if (info->field[i]->mod->hp > 0) {
        heal = heal - info->field[i]->mod->hp;
        info->field[i]->mod->hp = 0;
    }
    cap->entity_hit[i] = heal;
}

void k_throw_enscent(combat_t *info, int self, int focus, cap_info_t *cap)
{
    for (int i = 0; i < NB_ENTITY_SQUAD; ++i) {
        if (info->field[i] != NULL && info->field[i]->status != DEAD) {
            heal_entity(info, self, i, cap);
        }
    }
}
