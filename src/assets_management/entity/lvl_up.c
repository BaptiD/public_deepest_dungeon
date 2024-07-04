/*
** EPITECH PROJECT, 2024
** B-MUL-200-PAR-2-1-myrpg-pierre.pruvost
** File description:
** lvl_up.c
*/

#include "game.h"

static void update_stat(entity_t *entity, int stat_to_upd)
{
    if (stat_to_upd == ATK)
        entity->stats->atk += UP_ATK;
    if (stat_to_upd == HP)
        entity->stats->hp += UP_HP;
    if (stat_to_upd == SPD)
        entity->stats->spd += UP_SPD;
    if (stat_to_upd == CRT)
        entity->stats->crt += UP_CRT;
    if (stat_to_upd == PRE)
        entity->stats->pre += UP_PRE;
    return;
}

void level_up_entity(entity_t *entity, display_t *display,
    int identity, int lvl_gain)
{
    int stat_to_upd = -1;

    while (lvl_gain > 0) {
        if (identity == MONSTER_ENTITY) {
            stat_to_upd = arc4random() % (NB_STATS - 2);
            update_stat(entity, stat_to_upd);
        } else {
            stat_to_upd = arc4random() % (NB_STATS - 2);
            stat_to_upd = chose_stat(display, entity, entity);
            update_stat(entity, stat_to_upd);
        }
        lvl_gain -= 1;
    }
    entity->stats->hp += 2;
}
