/*
** EPITECH PROJECT, 2024
** B-MUL-200-PAR-2-1-myrpg-pierre.pruvost
** File description:
** add_entity_to_squad.c
*/
#include "combat.h"
#include "my.h"

void add_entity_to_squad(entity_t *entity_squad, entity_t *new_entity,
    int pose)
{
    logs(INFO, "Add entity to entity squad...");
    if (entity_squad->squad[pose] != NULL) {
        logs(ERROR, "Can't set entity where there is allready one");
    } else {
        entity_squad->squad[pose] = new_entity;
        logs(SUCCESS, "Entity added OK");
    }
}
