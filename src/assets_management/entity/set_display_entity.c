/*
** EPITECH PROJECT, 2024
** B-MUL-200-PAR-2-1-myrpg-pierre.pruvost
** File description:
** set_display_entity.c
*/
#include "entity.h"
#include "maps.h"
#include "combat.h"

void set_entity_sprite_explo(entity_t *entity, int entity_enum)
{
    entity->display[EXPLO_STATE] = malloc(sizeof(sprite_t));
    entity->display[EXPLO_STATE]->sprite = sfSprite_create();
    entity->display[EXPLO_STATE]->texture = sfTexture_createFromFile(
        ENTITY_EXPLO_SPRITE_FILEPATH[ID_IDLE_RIGHT + entity->id], NULL);
    entity->rect = (sfIntRect){0, 0, 32, 32};
    sfSprite_setTexture(entity->display[EXPLO_STATE]->sprite,
        entity->display[EXPLO_STATE]->texture, sfTrue);
    sfSprite_setPosition(entity->display[EXPLO_STATE]->sprite, (sfVector2f){
        MAP_SQUARE * ((MAP_VISIBLE_X / 2) / MAP_SQUARE - entity->pos[0])
        + entity->pos[0] * MAP_SQUARE, MAP_SQUARE * ((MAP_VISIBLE_Y / 2) /
        MAP_SQUARE - entity->pos[1]) + entity->pos[1] * MAP_SQUARE});
    sfSprite_setTextureRect(entity->display[EXPLO_STATE]->sprite,
        entity->rect);
    sfSprite_setScale(entity->display[EXPLO_STATE]->sprite,
        (sfVector2f){MAP_SQUARE / 32, MAP_SQUARE / 32});
    entity->clock = sfClock_create();
}

void set_entity_sprite_combat(entity_t *entity, int entity_enum)
{
    sfVector2f ratio = {0, 0};

    entity->display[COMBAT_STATE] = malloc(sizeof(sprite_t));
    entity->display[COMBAT_STATE]->sprite = sfSprite_create();
    entity->display[COMBAT_STATE]->texture = sfTexture_createFromFile(
        COMBAT_ANIMATION[entity_enum][IDLE].path, NULL);
    sfSprite_setTexture(entity->display[COMBAT_STATE]->sprite,
        entity->display[COMBAT_STATE]->texture, sfTrue);
    sfSprite_setTextureRect(entity->display[COMBAT_STATE]->sprite,
        entity->rect);
    ratio.x = COMBAT_SPRITE_SIZE / COMBAT_ANIMATION[entity_enum][IDLE].frame_x;
    ratio.y = COMBAT_SPRITE_SIZE / COMBAT_ANIMATION[entity_enum][IDLE].frame_x;
    sfSprite_setScale(entity->display[COMBAT_STATE]->sprite, ratio);
    entity->status = IDLE;
}
