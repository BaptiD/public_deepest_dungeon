/*
** EPITECH PROJECT, 2024
** B-MUL-200-PAR-2-1-myrpg-pierre.pruvost
** File description:
** chose_focus_capa.c
*/

#include "capacity.h"
#include "my.h"


static void close_event(sfRenderWindow *window, sfEvent event)
{
    while (sfRenderWindow_pollEvent(window, &event))
        if (event.type == sfEvtClosed)
            sfRenderWindow_close(window);
}

static void set_sound_type(sfMusic **sounds, cap_info_t *cap)
{
    for (int i = 0; i < NB_ENTITY_SQUAD * 2; ++i) {
        if (cap->type[i] == CRIT)
            play_sound(sounds[ATK_1_WAV]);
        if (cap->type[i] == HEAL || cap->type[i] == HEAL_CRIT)
            play_sound(sounds[HEAL]);
        if (cap->type[i] == STAT_DOWN)
            play_sound(sounds[DEBUFF_WAV]);
        if (cap->type[i] == STAT_UP)
            play_sound(sounds[BUFF_WAV]);
        if (cap->type[i] == BASIC)
            play_sound(sounds[ATK_2_WAV]);
        if (cap->type[i] == MISS)
            play_sound(sounds[MISS_WAV]);
    }
}

static void interaction_display_loop(display_t *display,
    combat_t *info, cap_info_t *cap)
{
    my_clock_t *clock = set_clock();
    sfEvent event;

    set_sound_type(display->sounds, cap);
    while (sfRenderWindow_isOpen(display->window) &&
        time_elapsed(clock->time, 2.2) != sfTrue) {
        close_event(display->window, event);
        clock_restart(info);
        anim_idle_field(info);
        draw_combat(display, info);
        display_damage_hit(display, info, cap);
        sfRenderWindow_display(display->window);
    }
    destory_clock(clock);
}

sfBool can_focus(combat_t *info, int focus)
{
    if (info->field[focus] == NULL || info->field[focus]->status == DEAD) {
        return sfFalse;
    }
    if (CAPACITY[info->field[info->turn]->capacities[info->capa_pressed - 3]]
        .type == SELF && info->turn == focus)
        return sfTrue;
    if (CAPACITY[info->field[info->turn]->capacities[info->capa_pressed - 3]]
        .focus[focus] == 1)
        return sfTrue;
    return sfFalse;
}

sfBool position_capa(combat_t *info, entity_t *entity, int key)
{
    if (CAPACITY[entity->capacities[key - 3]].range[info->turn] == 1)
        return sfTrue;
    return sfFalse;
}

static sfBool can_hit_someone(combat_t *info, int capa)
{
    for (int i = 0; i < NB_ENTITY_SQUAD; ++i) {
        if (CAPACITY[info->field[info->turn]->capacities[capa - 3]].focus[i]
            == 1 && info->field[i] != NULL && info->field[i]->status != DEAD)
            return sfTrue;
    }
    return sfFalse;
}

void monster_capacity_event(display_t *display, combat_t *info)
{
    int random_focus = arc4random() % 4;

    info->capa_pressed = arc4random() % 4 + 3;
    while (can_hit_someone(info, info->capa_pressed) != sfTrue)
        info->capa_pressed = arc4random() % 4 + 3;
    while (can_focus(info, random_focus) != sfTrue)
        random_focus = arc4random() % 4;
    capacity_event(display, info, info->capa_pressed, random_focus);
}

void capacity_event(display_t *display, combat_t *info, int key,
    int focus)
{
    cap_info_t *cap = NULL;

    cap = launch_capacity(info, focus,
        info->field[info->turn]->capacities[key - 3], key);
    info->capa_pressed = 0;
    interaction_display_loop(display, info, cap);
    next_turn(display, info);
    free(cap);
}
