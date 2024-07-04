/*
** EPITECH PROJECT, 2024
** B-MUL-200-PAR-2-1-myrpg-pierre.pruvost
** File description:
** basics.c
*/

#include "combat.h"

sfBool is_hitting(entity_t *attack, entity_t *defend)
{
    int hit = 0;
    int prot = 0;

    if (defend != NULL)
        prot = (defend->stats->pro + defend->mod->pro) * PROT_RATIO;
    hit = arc4random() % 100;
    if (hit > attack->stats->pre + attack->mod->pre + prot)
        return sfFalse;
    return sfTrue;
}

sfBool crit_chance(entity_t *attack, entity_t *defend)
{
    int crit = 0;
    int prot = 0;

    if (defend != NULL)
        prot = (defend->stats->pro + defend->mod->pro) * PROT_RATIO;
    crit = arc4random() % 100;
    if (crit < attack->stats->crt + attack->mod->crt + prot)
        return sfTrue;
    return sfFalse;
}

void attack_entity(combat_t *info, int focus, cap_info_t *cap, int mod)
{
    int hit = info->field[info->turn]->stats->atk + info->field
        [info->turn]->mod->atk + (arc4random() % (1 - (-1) + 1) + (-1)) + mod;

    if (hit < 0)
        hit = 0;
    if (is_hitting(info->field[info->turn], info->field[focus]) == sfFalse) {
        cap->entity_hit[focus] = 0;
        cap->type[focus] = MISS;
        return;
    }
    if (crit_chance(info->field[info->turn], info->field[focus]) == sfTrue) {
        info->field[focus]->mod->hp -= hit * CRIT_RATIO;
        cap->entity_hit[focus] = hit * CRIT_RATIO;
        cap->type[focus] = CRIT;
    } else {
        info->field[focus]->mod->hp -= hit;
        cap->entity_hit[focus] = hit;
        cap->type[focus] = BASIC;
    }
    hit_animation(info, focus);
}
