/*
** EPITECH PROJECT, 2024
** B-MUL-200-PAR-2-1-myrpg-pierre.pruvost
** File description:
** effect_interaction.c
*/

#include "combat.h"

void stun_entity(entity_t *entity, int chance)
{
    if (entity->effects.stun[NB_TURN_EFFECT] == 0)
        entity->effects.stun[NB_TURN_EFFECT] = 1;
}

void burn_entity(entity_t *entity, int chance, int damages, int turn)
{
    int chance_hit = arc4random() % 100;

    if (chance_hit > chance)
        return;
    if (entity->effects.burn[NB_TURN_EFFECT] > 0)
        entity->effects.burn[DAMAGES_EFFECT] += damages;
    else {
        entity->effects.burn[NB_TURN_EFFECT] = turn;
        entity->effects.burn[DAMAGES_EFFECT] = damages;
    }
}

void bleed_entity(entity_t *entity, int chance, int damages, int turn)
{
    int chance_hit = arc4random() % 100;

    if (chance_hit > chance)
        return;
    if (entity->effects.bleed[NB_TURN_EFFECT] > 0)
        entity->effects.bleed[DAMAGES_EFFECT] += damages;
    else {
        entity->effects.bleed[NB_TURN_EFFECT] = turn;
        entity->effects.bleed[DAMAGES_EFFECT] = damages;
    }
}

void poison_entity(entity_t *entity, int chance, int damages, int turn)
{
    int chance_hit = arc4random() % 100;

    if (chance_hit > chance)
        return;
    if (entity->effects.poison[NB_TURN_EFFECT] > 0)
        entity->effects.poison[DAMAGES_EFFECT] += damages;
    else {
        entity->effects.poison[NB_TURN_EFFECT] = turn;
        entity->effects.poison[DAMAGES_EFFECT] = damages;
    }
}
