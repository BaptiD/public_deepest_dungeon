/*
** EPITECH PROJECT, 2024
** B-MUL-200-PAR-2-1-myrpg-pierre.pruvost
** File description:
** clear_entity.c
*/

#include "entity.h"

void destroy_entities(entity_t *entity)
{
    free(entity->stats);
    free(entity->mod);
    free(entity->squad);
    sfClock_destroy(entity->clock);
    free(entity);
}
