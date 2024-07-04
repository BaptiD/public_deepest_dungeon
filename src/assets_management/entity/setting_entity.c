/*
** EPITECH PROJECT, 2024
** B-MUL-200-PAR-2-1-myrpg-pierre.pruvost
** File description:
** setting_entity.c
*/
#include "entity.h"
#include "combat.h"
#include "my.h"
#include "maps.h"
#include <string.h>

static void set_spells(char *line, entity_t **entity)
{
    char **line_arr = my_str_to_word_arr(line, ';');

    for (int i = 0; line_arr[i] != NULL && i < 4; ++i) {
        (*entity)->capacities[i] = atoi(line_arr[i]);
    }
    free_arr(line_arr);
}

static void set_xp(char *line, entity_t **entity)
{
    char **line_arr = my_str_to_word_arr(line, ';');

    (*entity)->level = atoi(line_arr[0]);
    (*entity)->xp = atoi(line_arr[1]);
    free_arr(line_arr);
}

static void get_name(char *line, entity_t **entity)
{
    int i = 0;

    for (i; i < strlen(line) && line[i] != '\0'; ++i) {
        (*entity)->name[i] = line[i];
    }
    (*entity)->name[i] = '\0';
}

static void set_info_file(entity_t *entity, char **file)
{
    for (int i = 0; file[i] != NULL; ++i) {
        if (strcmp(file[i], NAME_ENT) == 0 && file[i + 1] != NULL)
            get_name(file[i + 1], &entity);
        if (strcmp(file[i], STATS_ENT) == 0 && file[i + 1] != NULL)
            entity->stats = set_stats(file[i + 1]);
        if (strcmp(file[i], CAPA_ENT) == 0 && file[i + 1] != NULL)
            set_spells(file[i + 1], &entity);
        if (strcmp(file[i], XP_ENT) == 0 && file[i + 1] != NULL)
            set_xp(file[i + 1], &entity);
    }
}

static void set_inventory_empty(entity_t *actuall_entity)
{
    for (int k = 0; k < INVENTORY_SIZE; k++) {
        actuall_entity->inventory[k] = -1;
    }
    for (int k = 0; k < NB_ITEMS_SQUAD; k++) {
        actuall_entity->items[k] = -1;
    }
}

static entity_t **set_entity_squad(entity_t *actuall_entity)
{
    entity_t **squad = malloc(sizeof(entity_t *) * NB_ENTITY_SQUAD);

    for (int i = 0; i < NB_ENTITY_SQUAD; ++i)
        squad[i] = NULL;
    squad[NB_ENTITY_SQUAD - 1] = actuall_entity;
    return squad;
}

static entity_t *set_entity(char **file, int entity_enum)
{
    entity_t *entity = malloc(sizeof(entity_t));

    if (entity == NULL) {
        logs(ERROR, "Malloc failed");
        return NULL;
    }
    entity->id = entity_enum;
    set_info_file(entity, file);
    entity->mod = set_mod_empty();
    set_inventory_empty(entity);
    entity->pos[0] = 10;
    entity->pos[1] = 10;
    set_entity_sprite_explo(entity, entity_enum);
    set_entity_sprite_combat(entity, entity_enum);
    entity->effects = set_empty_effects();
    entity->squad = set_entity_squad(entity);
    entity->orientation = RIGHT;
    return entity;
}

entity_t *setting_entity_from_file(int entity_enum)
{
    entity_t *entity = NULL;
    char **file_arr = NULL;

    logs(INFO, "Setting entity from file...");
    logs(INFO, "Opening file...");
    file_arr = get_file_as_arr(ENTITY_INFO_FILEPATH[entity_enum]);
    if (file_arr == NULL) {
        logs(ERROR, "Reading file error");
        return NULL;
    }
    logs(SUCCESS, "File open OK");
    entity = set_entity(file_arr, entity_enum);
    if (entity == NULL)
        return NULL;
    logs(SUCCESS, "Entity set OK");
    return entity;
}
