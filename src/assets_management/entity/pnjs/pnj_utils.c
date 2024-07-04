/*
** EPITECH PROJECT, 2024
** pnj_utils
** File description:
** functions to manage/use pnjs
*/

#include "entity.h"
#include "game.h"
#include "combat.h"
#include "my.h"

static bool is_it_in_squad(entity_t *player, int type)
{
    for (size_t i = 0; i < 4; i++) {
        if (player->squad[i] != NULL && player->squad[i]->id == type)
            return true;
    }
    return false;
}

static pnj_t *find_pnj_not_in_squad(pnj_t **pnjs, entity_t *player)
{
    for (size_t i = 0; i < NB_PNJ; i++) {
        if (is_it_in_squad(player, pnjs[i]->type) == false)
            return pnjs[i];
    }
    return NULL;
}

static bool is_all_pnj_used(pnj_t **pnjs)
{
    int nb_used = 0;

    for (size_t i = 0; i < NB_PNJ; i++) {
        if (pnjs[i]->pos[0] == -1)
            nb_used++;
    }
    if (nb_used == NB_PNJ)
        return true;
    else
        return false;
}

pnj_t *find_p_not_used(pnj_t **pnjs, entity_t *player)
{
    int id = 0;

    if (is_all_pnj_used(pnjs) == true)
        return find_pnj_not_in_squad(pnjs, player);
    while (1) {
        id = arc4random() % (NB_PNJ - 1);
        if (pnjs[id]->pos[0] == -1)
            return pnjs[id];
    }
    return NULL;
}

static void set_new_pnj(pnj_t **pnjs, sfVector2i room, int *pos,
    entity_t *player)
{
    pnj_t *pnj = find_p_not_used(pnjs, player);

    if (pnj == NULL)
        return;
    pnj->co_room = room;
    pnj->pos[0] = pos[0];
    pnj->pos[1] = pos[1];
}

void set_pnj(pnj_t **pnjs, maps_t *map, int *pos, entity_t *player)
{
    if (map->char_map[pos[1]][pos[0]] != MAP_PNJ)
        return;
    for (size_t i = 0; i < NB_PNJ; i++) {
        if (pnjs[i]->co_room.x == map->co_map.x &&
            pnjs[i]->co_room.y == map->co_map.y &&
            pnjs[i]->pos[0] == pos[0] && pnjs[i]->pos[1] == pos[1])
            return;
    }
    set_new_pnj(pnjs, map->co_map, pos, player);
}

void set_pnj_in_map(maps_t *map, pnj_t **pnjs, entity_t *player)
{
    int pos[2];

    for (size_t y = 1; y < 20; y++) {
        for (size_t x = 1; x < 20; x++) {
            pos[0] = x;
            pos[1] = y;
            set_pnj(pnjs, map, pos, player);
        }
    }
}
