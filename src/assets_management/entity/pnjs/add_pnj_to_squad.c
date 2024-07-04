/*
** EPITECH PROJECT, 2024
** add_pnj_to_group
** File description:
** functions to transform a pnj to an entity and add it to the crew
*/

#include "entity.h"
#include "game.h"
#include "combat.h"

int squad_size(entity_t *player)
{
    int nb = 0;

    for (int i = 0; i < NB_ENTITY_SQUAD; i++)
        if (player->squad[i] != NULL)
            nb++;
    return nb;
}

int find_id_empty(entity_t *player)
{
    for (int i = 3; i > 0; i--)
        if (player->squad[i] == NULL)
            return i;
    return -1;
}

entity_t *transform_pnj_to_entity(pnj_t *pnj)
{
    entity_t *new_pnj;

    new_pnj = setting_entity_from_file(pnj->type);
}

void add_pnj_to_squad(entity_t *player, pnj_t *pnj)
{
    int id_empty = find_id_empty(player);

    if (id_empty == -1 || id_empty > 3)
        return;
    player->squad[id_empty] = transform_pnj_to_entity(pnj);
}
