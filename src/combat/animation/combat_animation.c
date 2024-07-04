/*
** EPITECH PROJECT, 2024
** B-MUL-200-PAR-2-1-myrpg-pierre.pruvost
** File description:
** idle_animation.c
*/

#include "combat.h"

static int short_animation(entity_t *entity)
{
    if (entity->status == IDLE)
        return CONTINUE;
    if (entity != NULL &&
        entity->rect.left + COMBAT_ANIMATION[entity->id][entity->status]
        .frame_x + 1 > COMBAT_ANIMATION[entity->id][entity->status].x_max) {
        if (entity->status == DEAD)
            return STOP;
        change_sprite_action(entity, IDLE);
        return CONTINUE;
    }
    return CONTINUE;
}

void hit_animation(combat_t *info, int focus)
{
    if (info->field[focus]->status != DEAD) {
        if (is_alive(info->field[focus]) == sfFalse)
            change_sprite_action(info->field[focus], DEAD);
        else
            change_sprite_action(info->field[focus], HURT);
    }
}

static void move_rect_sprite_combat(entity_t *entity)
{
    if (entity == NULL || short_animation(entity) == STOP)
        return;
    if (entity->rect.left + COMBAT_ANIMATION[entity->id][entity->status]
        .frame_x + 1 > COMBAT_ANIMATION[entity->id][entity->status].x_max) {
        entity->rect.left = 0;
        sfSprite_setTextureRect(entity->display[COMBAT_STATE]->sprite,
            entity->rect);
    } else {
        entity->rect.left += COMBAT_ANIMATION[entity->id][entity->status]
            .frame_x;
        sfSprite_setTextureRect(entity->display[COMBAT_STATE]->sprite,
            entity->rect);
    }
}

void anim_idle_field(combat_t *info)
{
    sfTime time;
    float seconds;

    time = sfClock_getElapsedTime(info->clock);
    seconds = time.microseconds / 1000000.0;
    if (seconds > (ANIMATION_SPEED * info->index_clock)) {
        for (int i = 0; i < NB_ENTITY_SQUAD * 2; ++i)
            move_rect_sprite_combat(info->field[i]);
        info->index_clock += 1;
    }
}
