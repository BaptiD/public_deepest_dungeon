/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** statics.h
*/

#ifndef OPTIONS_H_
    #define OPTIONS_H_
    #include <SFML/Graphics.h>

    #define NB_SOUND_BARS 2

    #define MUSIC_SPEAKER 0
    #define EFFECTS_SPEAKER 1

    #define START_BALL 690.0
    #define END_BALL 1190.0
    #define BALL_DISTANCE (double)(END_BALL - START_BALL)

    #define SPEAKER_SIZE (sfVector2f){70, 70}
    #define BALL_SIZE (sfVector2f){39, 39}

static const sfVector2f SPEAKER_ON_POS[] = {
    {1279, 393},
    {1279, 584}
};

static const sfVector2f SPEAKER_OFF_POS[] = {
    {586, 393},
    {586, 584}
};

static const int BALL_Y[] = {
    408,
    599
};

void display_options(display_t *display, sprite_t *sprites, int *hover);
void check_speakers(display_t *display, sprite_t *sprites, sfVector2i pos);
void check_balls(display_t *display, sprite_t *sprites, sfVector2i pos);
void drag_n_drop_music(display_t *display, sprite_t *sprites);
void drag_n_drop_effects(display_t *display, sprite_t *sprites);

#endif
