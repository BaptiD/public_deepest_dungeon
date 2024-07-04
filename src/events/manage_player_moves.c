/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** manane player moving
*/

#include "game.h"
#include "combat.h"
#include "my.h"

static void set_rect_entity(entity_t *player)
{
    player->rect = (sfIntRect){16, 32, 32, 32};
    sfSprite_setTextureRect(player->display[EXPLO_STATE]->sprite,
        player->rect);
    if (player->orientation == LEFT)
        player->display[EXPLO_STATE]->texture = sfTexture_createFromFile(
            ENTITY_EXPLO_SPRITE_FILEPATH[ID_RUN_LEFT + player->id], NULL);
    else
        player->display[EXPLO_STATE]->texture = sfTexture_createFromFile(
        ENTITY_EXPLO_SPRITE_FILEPATH[ID_RUN_RIGHT + player->id], NULL);
    sfSprite_setTexture(player->display[EXPLO_STATE]->sprite,
        player->display[EXPLO_STATE]->texture, sfTrue);
}

static void actu_rect_dungeon(dungeon_t *dungeon, entity_t *entity, int i)
{
    if (entity->movement == RIGHT)
        move_map(dungeon, -(MOVE_EXPLO_ANIM), 0);
    if (entity->movement == LEFT)
        move_map(dungeon, (MOVE_EXPLO_ANIM), 0);
    if (entity->movement == UP)
        move_map(dungeon, 0, (MOVE_EXPLO_ANIM));
    if (entity->movement == DOWN)
        move_map(dungeon, 0, -(MOVE_EXPLO_ANIM));
}

static double move_rect(dungeon_t *dungeon, entity_t *entity, sfTime time,
    int i)
{
    if (time.microseconds > 99999) {
        if (entity->rect.left + 64 > 336)
            entity->rect.left = 16;
        else
            entity->rect.left += 64;
        sfClock_restart(entity->clock);
        actu_rect_dungeon(dungeon, entity, i);
        return MOVE_EXPLO_ANIM;
    }
    return 0;
}

static double run_rect_sprite(entity_t *entity, display_t *display,
    dungeon_t *dungeon)
{
    sfClock *clock = sfClock_create();
    sfTime anim_time = sfClock_getElapsedTime(clock);
    sfTime time_player;
    double index = 0;

    set_rect_entity(entity);
    for (size_t i = 0; anim_time.microseconds < 500000; i++) {
        anim_time = sfClock_getElapsedTime(clock);
        time_player = sfClock_getElapsedTime(entity->clock);
        index += move_rect(dungeon, entity, time_player, i);
        sfSprite_setTextureRect(entity->display[EXPLO_STATE]->sprite,
            entity->rect);
        display_map(display, dungeon);
        sfRenderWindow_drawSprite(display->window,
            entity->display[EXPLO_STATE]->sprite, NULL);
        sfRenderWindow_display(display->window);
        sfRenderWindow_clear(display->window, BG_DEFAULT_COLOR);
    }
    sfClock_destroy(clock);
    return index;
}

static sfBool can_move_here(char c)
{
    if (c == ' ' || c == 'D')
        return sfTrue;
    return sfFalse;
}

static void move_in_map(entity_t *p, display_t *display, dungeon_t *dungeon,
    int side)
{
    double index = 0;

    if (side == UP) {
        p->pos[1] -= 1;
        p->movement = UP;
        index = run_rect_sprite(p, display, dungeon);
        move_map(dungeon, 0, 1 - index);
    }
    if (side == DOWN) {
        p->pos[1] += 1;
        p->movement = DOWN;
        index = run_rect_sprite(p, display, dungeon);
        move_map(dungeon, 0, -1 + index);
    }
}

static void move_in_map_right_left(entity_t *player, display_t *display,
    dungeon_t *dungeon, int side)
{
    maps_t map = ACTUAL_MAP;
    double index = 0;

    if (side == LEFT) {
        player->pos[0] -= 1;
        player->orientation = LEFT;
        player->movement = LEFT;
        index = run_rect_sprite(player, display, dungeon);
        move_map(dungeon, 1 - index, 0);
    }
    if (side == RIGHT) {
        player->pos[0] += 1;
        player->orientation = RIGHT;
        player->movement = RIGHT;
        index = run_rect_sprite(player, display, dungeon);
        move_map(dungeon, -1 + index, 0);
    }
}

static void up_down_right_left(entity_t *p, display_t *display,
    dungeon_t *dungeon)
{
    maps_t map = ACTUAL_MAP;

    if (sfKeyboard_isKeyPressed(sfKeyZ))
        if (p->pos[1] > 0 && can_move_here(map.char_map[p->pos[1] - 1]
            [p->pos[0]]) == sfTrue)
            move_in_map(p, display, dungeon, UP);
    if (sfKeyboard_isKeyPressed(sfKeyS))
        if (p->pos[1] < 19 && can_move_here(map.char_map[p->pos[1] + 1]
            [p->pos[0]]) == sfTrue)
            move_in_map(p, display, dungeon, DOWN);
    if (sfKeyboard_isKeyPressed(sfKeyQ))
        if (p->pos[0] > 0 && can_move_here(map.char_map[p->pos[1]]
            [p->pos[0] - 1]) == sfTrue)
            move_in_map_right_left(p, display, dungeon, LEFT);
    if (sfKeyboard_isKeyPressed(sfKeyD))
        if (p->pos[0] < 19 && can_move_here(map.char_map[p->pos[1]]
            [p->pos[0] + 1]) == sfTrue)
            move_in_map_right_left(p, display, dungeon, RIGHT);
}

void move_key(entity_t *player, display_t *display, dungeon_t *dungeon)
{
    up_down_right_left(player, display, dungeon);
    if (player->orientation == LEFT)
        player->display[EXPLO_STATE]->texture = sfTexture_createFromFile(
            ENTITY_EXPLO_SPRITE_FILEPATH[ID_IDLE_LEFT + player->id], NULL);
    else
        player->display[EXPLO_STATE]->texture = sfTexture_createFromFile(
            ENTITY_EXPLO_SPRITE_FILEPATH[ID_IDLE_RIGHT + player->id], NULL);
    sfSprite_setTexture(player->display[EXPLO_STATE]->sprite,
        player->display[EXPLO_STATE]->texture, sfTrue);
    player->rect = (sfIntRect){0, 0, 32, 32};
    sfSprite_setTextureRect(player->display[EXPLO_STATE]->sprite,
        player->rect);
}
