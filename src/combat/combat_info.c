/*
** EPITECH PROJECT, 2024
** B-MUL-200-PAR-2-1-myrpg-pierre.pruvost
** File description:
** status.c
*/

#include "combat.h"
#include "my.h"
#include <stdbool.h>

static int get_player_pos(entity_t *player)
{
    for (int k = 0; k < NB_ENTITY_SQUAD; k++) {
        if (player->squad[k] != NULL && player->squad[k]->id == player->id)
            return k;
    }
    return ERROR;
}

sfBool is_combat_finished(combat_t *info, entity_t *player, display_t *display)
{
    int player_pos = get_player_pos(player);

    if (player->status == DEAD) {
        if (player_pos != ERROR)
            display_death_player(display, player, player_pos);
        return sfTrue;
    }
    for (int i = NB_ENTITY_SQUAD; i < NB_ENTITY_SQUAD * 2; ++i) {
        if (info->field[i] != NULL && info->field[i]->status != DEAD)
            return sfFalse;
    }
    display_xp_gain(info, display);
    return sfTrue;
}

sfBool next_combat_start(dungeon_t *dungeon, entity_t *player, int x, int y)
{
    if (player->pos[1] + y >= 0 && player->pos[1] + y <= 19 &&
        player->pos[0] + x >= 0 && player->pos[0] + x <= 19) {
        if (ACTUAL_MAP.char_map[player->pos[1] + y][player->pos[0] + x]
            == MAP_MONSTER) {
            ACTUAL_MAP.char_map[player->pos[1] + y][player->pos[0] + x] = ' ';
            logs(INFO, "Combat starting...");
            return sfTrue;
        }
    }
    return sfFalse;
}

sfBool is_combat_start(dungeon_t *dungeon, entity_t *player)
{
    if (next_combat_start(dungeon, player, -1, -1) == sfTrue)
        return sfTrue;
    if (next_combat_start(dungeon, player, -1, 0) == sfTrue)
        return sfTrue;
    if (next_combat_start(dungeon, player, -1, 1) == sfTrue)
        return sfTrue;
    if (next_combat_start(dungeon, player, 0, -1) == sfTrue)
        return sfTrue;
    if (next_combat_start(dungeon, player, 0, 1) == sfTrue)
        return sfTrue;
    if (next_combat_start(dungeon, player, 1, -1) == sfTrue)
        return sfTrue;
    if (next_combat_start(dungeon, player, 1, 0) == sfTrue)
        return sfTrue;
    if (next_combat_start(dungeon, player, 1, 1) == sfTrue)
        return sfTrue;
    return sfFalse;
}

void change_sprite_action(entity_t *entity, int action)
{
    entity->rect.left = 0;
    sfTexture_destroy(entity->display[COMBAT_STATE]->texture);
    entity->display[COMBAT_STATE]->texture = sfTexture_createFromFile(
        COMBAT_ANIMATION[entity->id][action].path, NULL);
    sfSprite_setTexture(entity->display[COMBAT_STATE]->sprite,
        entity->display[COMBAT_STATE]->texture, sfTrue);
    sfSprite_setTextureRect(entity->display[COMBAT_STATE]->sprite,
            entity->rect);
    entity->status = action;
}

sfBool is_alive(entity_t *entity)
{
    if (entity->stats->hp + entity->mod->hp > 0)
        return sfTrue;
    return sfFalse;
}
