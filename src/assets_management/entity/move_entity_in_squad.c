/*
** EPITECH PROJECT, 2024
** B-MUL-200-PAR-2-1-myrpg-pierre.pruvost
** File description:
** move_entity_in_squad.c
*/

#include "entity.h"

void swap_entity(entity_t *player, int index_1, int index_2)
{
    entity_t *temp = player->squad[index_1];

    if (temp == NULL)
        return;
    player->squad[index_1] = player->squad[index_2];
    player->squad[index_2] = temp;
}
