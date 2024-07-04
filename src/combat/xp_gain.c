/*
** EPITECH PROJECT, 2024
** B-MUL-200-PAR-2-1-myrpg-pierre.pruvost
** File description:
** xp_gain.c
*/

#include "combat.h"
#include <stdio.h>
#include "math.h"

static void close_event(sfRenderWindow *window, sfEvent event)
{
    while (sfRenderWindow_pollEvent(window, &event))
        if (event.type == sfEvtClosed)
            sfRenderWindow_close(window);
}

static int get_total_enemy_xp(combat_t *info)
{
    int xp = 0;

    for (int i = NB_ENTITY_SQUAD; i < NB_ENTITY_SQUAD * 2; ++i) {
        if (info->field[i] != NULL && info->field[i]->status == DEAD) {
            xp += info->field[i]->xp * ((info->field[i]->level) *
                RATIO_XP_LVL_UP);
        }
    }
    return xp * RATIO_XP_MONSTER_KILL;
}

static int get_nb_ally(combat_t *info)
{
    int nb = 0;

    for (int i = 0; i < NB_ENTITY_SQUAD; ++i) {
        if (info->field[i] != NULL && info->field[i]->status != DEAD)
            nb += 1;
    }
    if (nb == 0)
        return 1;
    return nb;
}

static void xp_and_lvl_up(entity_t *entity, int xp_gain, display_t *display)
{
    int overflow = 0;

    entity->xp += xp_gain;
    if (entity->xp >= XP_TO_LVL_UP * pow(RATIO_XP_LVL_UP, entity->level)) {
        overflow = entity->xp -
            XP_TO_LVL_UP * pow(RATIO_XP_LVL_UP, entity->level);
        entity->level += 1;
        entity->xp = overflow;
        level_up_entity(entity, display, ALLY_ENTITY, 1);
    }
}

static int xp_gain(combat_t *info, display_t *display, int xp)
{
    for (int i = 0; i < NB_ENTITY_SQUAD; ++i) {
        if (info->field[i] != NULL && info->field[i]->status != DEAD) {
            display_xp_combat(display, info, xp, i);
        }
    }
}

static int get_xp_by_player(combat_t *info, display_t *display)
{
    int total_xp = get_total_enemy_xp(info);
    int nb_ally = get_nb_ally(info);
    int xp_by_player = total_xp / nb_ally;

    for (int i = 0; i < NB_ENTITY_SQUAD; ++i) {
        if (info->field[i] != NULL && info->field[i]->status != DEAD) {
            xp_and_lvl_up(info->field[i], xp_by_player, display);
        }
    }
    return xp_by_player;
}

void display_xp_gain(combat_t *info, display_t *display)
{
    sfClock *clock = sfClock_create();
    sfTime time;
    float seconds = 0;
    sfEvent event;
    int xp = get_xp_by_player(info, display);

    while (sfRenderWindow_isOpen(display->window) && seconds < 1.5) {
        time = sfClock_getElapsedTime(clock);
        seconds = time.microseconds / 1000000.0;
        close_event(display->window, event);
        clock_restart(info);
        anim_idle_field(info);
        draw_combat(display, info);
        xp_gain(info, display, xp);
        sfRenderWindow_display(display->window);
    }
    sfClock_destroy(clock);
}
