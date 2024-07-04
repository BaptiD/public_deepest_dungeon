/*
** EPITECH PROJECT, 2024
** event_menu_file.c
** File description:
** managing event
*/

#include "entity.h"
#include "game.h"
#include "sprites.h"
#include "menus.h"
#include "options.h"


static char *manage_events(display_t *display, sfVector2i pos)
{
    sfEvent event;

    while (sfRenderWindow_pollEvent(display->window, &event)) {
        if (event.type == sfEvtClosed)
            sfRenderWindow_close(display->window);
    }
}

static void change_volume(display_t *display, sfVector2i pos)
{
    double calc = (((double)pos.x - BALL_SIZE.x / 2) - START_BALL);
    double ratio = calc / BALL_DISTANCE;

    if (ratio < 0)
        ratio = 0.0;
    if (ratio > 1)
        ratio = 1.0;
    for (int k = BG_MUSIC_WAV; k < WRONG_WAV; k++)
        sfMusic_setVolume(display->sounds[k], SOUND_VOLUME[k] * ratio);
}

void drag_n_drop_music(display_t *display, sprite_t *sprites)
{
    sfVector2i pos = sfMouse_getPosition((sfWindow *)display->window);
    int hover = OUT;

    while (sfMouse_isButtonPressed(sfMouseLeft) &&
        sfRenderWindow_isOpen(display->window)) {
        pos = sfMouse_getPosition((sfWindow *)display->window);
        manage_events(display, pos);
        change_volume(display, pos);
        display_options(display, sprites, &hover);
        sfRenderWindow_display(display->window);
    }
    return;
}
