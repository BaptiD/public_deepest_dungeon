/*
** EPITECH PROJECT, 2024
** B-MUL-200-PAR-2-1-myrpg-pierre.pruvost
** File description:
** close_combat.c
*/

#include "combat.h"
#include "my.h"

static void set_rect_back_to_explo(combat_t *info)
{
    for (int i = 0; i < NB_ENTITY_SQUAD * 2; ++i) {
        if (info->field[i] != NULL)
            info->field[i]->rect = (sfIntRect){0, 0, 32, 32};
    }
}

static void set_stats_mod_back(combat_t *info)
{
    for (int i = 0; i < NB_ENTITY_SQUAD * 2; ++i) {
        if (info->field[i] != NULL) {
            info->field[i]->mod->atk = 0;
            info->field[i]->mod->crt = 0;
            info->field[i]->mod->spd = 0;
            info->field[i]->mod->pre = 0;
            info->field[i]->mod->pro = 0;
        }
    }
}

static void free_combat(combat_t *info)
{
    free(info->field);
    free(info->played);
    sfClock_destroy(info->clock);
    free(info);
}

static void clear_monster_squad(combat_t *info)
{
    for (int i = NB_ENTITY_SQUAD; i < NB_ENTITY_SQUAD * 2; ++i) {
        if (info->field[i] != NULL) {
            destroy_entities(info->field[i]);
        }
    }
}

static void dead_ally_removing(combat_t *info, int player_id)
{
    for (int i = 0; i < NB_ENTITY_SQUAD; ++i) {
        if (info->field[i] != NULL && info->field[i]->status == DEAD &&
            info->field[i]->id != player_id) {
            destroy_entities(info->field[i]);
            info->field[i] = NULL;
        }
    }
}

void clear_combat(combat_t *info, int player_id)
{
    logs(INFO, "Clearing combat...");
    dead_ally_removing(info, player_id);
    set_rect_back_to_explo(info);
    set_stats_mod_back(info);
    clear_monster_squad(info);
    free_combat(info);
    logs(SUCCESS, "Combat cleared OK");
}
