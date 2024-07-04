/*
** EPITECH PROJECT, 2024
** B-MUL-200-PAR-2-1-myrpg-pierre.pruvost
** File description:
** do_effect.c
*/

#include "combat.h"

void do_basic_effect(entity_t *entity, int effect)
{
    if (effect == BLEED_EFFECT) {
        entity->effects.bleed[NB_TURN_EFFECT] -= 1;
        entity->mod->hp -= entity->effects.bleed[DAMAGES_EFFECT];
        if (entity->effects.bleed[NB_TURN_EFFECT] <= 0)
            entity->effects.bleed[DAMAGES_EFFECT] = 0;
    }
    if (effect == BURN_EFFECT) {
        entity->effects.burn[NB_TURN_EFFECT] -= 1;
        entity->mod->hp -= entity->effects.burn[DAMAGES_EFFECT];
        if (entity->effects.burn[NB_TURN_EFFECT] <= 0)
            entity->effects.burn[DAMAGES_EFFECT] = 0;
    }
    if (effect == POISON_EFFECT) {
        entity->effects.poison[NB_TURN_EFFECT] -= 1;
        entity->mod->hp -= entity->effects.poison[DAMAGES_EFFECT];
        if (entity->effects.poison[NB_TURN_EFFECT] <= 0)
            entity->effects.poison[DAMAGES_EFFECT] = 0;
    }
}

void do_effect_by_type(combat_t *info, int effect)
{
    do_basic_effect(info->field[info->turn], effect);
    if (effect == STUN_EFFECT) {
        info->field[info->turn]->effects.stun[NB_TURN_EFFECT] = -1;
    }
}
