/*
** EPITECH PROJECT, 2024
** event_menu_file.c
** File description:
** managing event
*/

#include <stdbool.h>

#include "menus.h"
#include "game.h"
#include "entity.h"
#include "my.h"
#include "sound.h"
#include "options.h"

void check_balls(display_t *display, sprite_t *sprites, sfVector2i pos)
{
    sfVector2f ball_pos = {0};
    double vol = 0;

    if (sfMusic_getVolume(display->sounds[0]) != 0)
        vol = sfMusic_getVolume(display->sounds[0]) / 15;
    ball_pos = (sfVector2f){START_BALL + ((END_BALL - START_BALL) * vol),
        BALL_Y[0]};
    if (is_in_zone(pos, ball_pos, BALL_SIZE) == true)
        return drag_n_drop_music(display, sprites);
    vol = 0;
    if (sfMusic_getVolume(display->sounds[2]) != 0)
        vol = sfMusic_getVolume(display->sounds[2]) / 30;
    ball_pos = (sfVector2f){START_BALL + ((END_BALL - START_BALL) * vol),
        BALL_Y[1]};
    if (is_in_zone(pos, ball_pos, BALL_SIZE) == true)
        return drag_n_drop_effects(display, sprites);
}

void check_speakers(display_t *display, sprite_t *sprites, sfVector2i pos)
{
    if (is_in_zone(pos, SPEAKER_OFF_POS[MUSIC_SPEAKER], SPEAKER_SIZE) == true) {
        sfMusic_setVolume(display->sounds[0], 0.0);
        sfMusic_setVolume(display->sounds[1], 0.0);
        return;
    }
    if (is_in_zone(pos, SPEAKER_ON_POS[MUSIC_SPEAKER], SPEAKER_SIZE) == true) {
        sfMusic_setVolume(display->sounds[0], SOUND_VOLUME[0]);
        sfMusic_setVolume(display->sounds[1], SOUND_VOLUME[1]);
        return;
    }
    if (is_in_zone(pos, SPEAKER_OFF_POS[EFFECTS_SPEAKER], SPEAKER_SIZE) == true) {
        for (int k = 2; k < NB_SOUNDS; k++)
            sfMusic_setVolume(display->sounds[k], 0.0);
        return;
    }
    if (is_in_zone(pos, SPEAKER_ON_POS[EFFECTS_SPEAKER], SPEAKER_SIZE) == true) {
        for (int k = 2; k < NB_SOUNDS; k++)
            sfMusic_setVolume(display->sounds[k], SOUND_VOLUME[k]);
        return;
    }
}
