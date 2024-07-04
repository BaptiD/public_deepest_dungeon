/*
** EPITECH PROJECT, 2024
** B-MUL-200-PAR-2-1-myrpg-pierre.pruvost
** File description:
** play_sound.c
*/

#include "sound.h"

void play_sound(sfMusic *sound)
{
    sfMusic_setPlayingOffset(sound, (sfTime){0});
    sfMusic_play(sound);
}
