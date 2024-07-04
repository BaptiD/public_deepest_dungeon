/*
** EPITECH PROJECT, 2024
** B-MUL-200-PAR-2-1-myrpg-pierre.pruvost
** File description:
** combat_arrival.c
*/

#include "combat.h"
#include "my.h"

static void close_event(sfRenderWindow *window, sfEvent event)
{
    while (sfRenderWindow_pollEvent(window, &event))
        if (event.type == sfEvtClosed)
            sfRenderWindow_close(window);
}

void combat_arrival(combat_t *info, display_t *display)
{
    sfClock *clock = sfClock_create();
    sfEvent event;

    play_sound(display->sounds[COMBAT_MUSIC_WAV]);
    sfMusic_setLoop(display->sounds[COMBAT_MUSIC_WAV], sfTrue);
    while (sfRenderWindow_isOpen(display->window) &&
        time_elapsed(clock, 1.0) != sfTrue) {
        close_event(display->window, event);
        sfRenderWindow_clear(display->window, sfBlack);
        clock_restart(info);
        anim_idle_field(info);
        sfRenderWindow_drawSprite(display->window,
            info->background.sprite, NULL);
        draw_filed_entity(display->window, info);
        sfRenderWindow_display(display->window);
    }
    sfClock_destroy(clock);
    next_turn(display, info);
}
