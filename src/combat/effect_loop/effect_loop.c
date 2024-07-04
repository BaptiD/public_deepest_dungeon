/*
** EPITECH PROJECT, 2024
** B-MUL-200-PAR-2-1-myrpg-pierre.pruvost
** File description:
** stun_skip_anim.c
*/

#include "combat.h"
#include "my.h"

static void close_event(sfRenderWindow *window, sfEvent event)
{
    while (sfRenderWindow_pollEvent(window, &event))
        if (event.type == sfEvtClosed)
            sfRenderWindow_close(window);
}

static void destroy_sprite_effect(sprite_t sp_effect)
{
    sfSprite_destroy(sp_effect.sprite);
    sfTexture_destroy(sp_effect.texture);
}

static sprite_t set_effect_sprite(int effect, entity_t *entity, int i)
{
    sprite_t sp_effect = {0};
    sfVector2f pos = sfSprite_getPosition(
            entity->display[COMBAT_STATE]->sprite);
    sfVector2f ratio = {0, 0};

    sp_effect.sprite = sfSprite_create();
    sp_effect.texture = sfTexture_createFromFile(EFFECT_FILEPATH[effect],
        NULL);
    sfSprite_setTexture(sp_effect.sprite, sp_effect.texture, sfTrue);
    pos.y += POS_EFFECT_Y;
    if (i >= NB_ENTITY_SQUAD)
        pos.x += MONSTER_POS_EFFECT_X;
    else
        pos.x += ALLY_POS_EFFECT_X;
    sfSprite_setPosition(sp_effect.sprite, pos);
    ratio.x = SIZE_EFFECT_WANTED / SIZEOF_EFFECT[effect];
    ratio.y = SIZE_EFFECT_WANTED / SIZEOF_EFFECT[effect];
    sfSprite_setScale(sp_effect.sprite, ratio);
    return sp_effect;
}

static sfIntRect set_rect_effect(sprite_t sp_effect, sfIntRect rect,
    combat_t *info, int effect)
{
    rect.left += SIZEOF_EFFECT[effect];
    if (rect.left >= SIZEOF_EFFECT[effect] * NB_IMAGES_EFFECT[effect].x) {
        rect.top += SIZEOF_EFFECT[effect];
        rect.left = 0;
    }
    if (rect.top >= SIZEOF_EFFECT[effect] * NB_IMAGES_EFFECT[effect].y) {
        rect.left = 0;
        rect.top = 0;
    }
    sfSprite_setTextureRect(sp_effect.sprite, rect);
    return rect;
}

static sfBool is_move_rect(my_clock_t *clock)
{
    if (time_elapsed(clock->time, clock->index * 0.11) == sfTrue) {
        clock->index += 1;
        return sfTrue;
    }
    return sfFalse;
}

static void display_effect_animation(display_t *display, combat_t *info,
    int effect, cap_info_t damages_info)
{
    my_clock_t *clock = set_clock();
    sfEvent event;
    sprite_t sp_effect = set_effect_sprite(effect,
        info->field[info->turn], info->turn);
    sfIntRect rect = {0, 0, SIZEOF_EFFECT[effect], SIZEOF_EFFECT[effect]};

    while (sfRenderWindow_isOpen(display->window) &&
        time_elapsed(clock->time, 1.2) != sfTrue) {
        close_event(display->window, event);
        clock_restart(info);
        anim_idle_field(info);
        draw_combat(display, info);
        display_damage_hit(display, info, &damages_info);
        if (is_move_rect(clock) == sfTrue)
            rect = set_rect_effect(sp_effect, rect, info, effect);
        sfRenderWindow_drawSprite(display->window, sp_effect.sprite, NULL);
        sfRenderWindow_display(display->window);
    }
    destory_clock(clock);
    destroy_sprite_effect(sp_effect);
}

static int get_damages(entity_t *entity, int effect)
{
    if (effect == BLEED_EFFECT)
        return entity->effects.bleed[DAMAGES_EFFECT];
    if (effect == BURN_EFFECT)
        return entity->effects.burn[DAMAGES_EFFECT];
    if (effect == POISON_EFFECT)
        return entity->effects.poison[DAMAGES_EFFECT];
    return IGNORE;
}

static cap_info_t set_damages_display(entity_t *entity, int effect, int index)
{
    cap_info_t cap = {0};

    for (int i = 0; i < NB_ENTITY_SQUAD * 2; ++i) {
        cap.entity_hit[i] = IGNORE;
        cap.type[i] = IGNORE;
    }
    cap.entity_hit[index] = get_damages(entity, effect);
    if (cap.entity_hit[index] == IGNORE)
        cap.type[index] = IGNORE;
    else
        cap.type[index] = BASIC;
    return cap;
}

int launch_effect_animation(display_t *display, combat_t *info, int effect)
{
    cap_info_t damages_info = set_damages_display(info->field[info->turn],
        effect, info->turn);

    do_effect_by_type(info, effect);
    if (effect != STUN_EFFECT)
        hit_animation(info, info->turn);
    play_sound(display->sounds[14 + effect]);
    display_effect_animation(display, info, effect, damages_info);
    if (info->field[info->turn]->status == DEAD || effect == STUN_EFFECT) {
        next_turn(display, info);
        return DEAD;
    }
    return IDLE;
}

void effect_manage(display_t *display, combat_t *info)
{
    if (info->field[info->turn]->effects.bleed[NB_TURN_EFFECT] > 0)
        if (launch_effect_animation(display, info, BLEED_EFFECT) == DEAD)
            return;
    if (info->field[info->turn]->effects.burn[NB_TURN_EFFECT] > 0)
        if (launch_effect_animation(display, info, BURN_EFFECT) == DEAD)
            return;
    if (info->field[info->turn]->effects.poison[NB_TURN_EFFECT] > 0)
        if (launch_effect_animation(display, info, POISON_EFFECT) == DEAD)
            return;
    if (info->field[info->turn]->effects.stun[NB_TURN_EFFECT] == -1)
        info->field[info->turn]->effects.stun[NB_TURN_EFFECT] == 0;
    if (info->field[info->turn]->effects.stun[NB_TURN_EFFECT] > 0)
        launch_effect_animation(display, info, STUN_EFFECT);
}
