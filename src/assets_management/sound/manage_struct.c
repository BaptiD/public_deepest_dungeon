/*
** EPITECH PROJECT, 2024
** B-MUL-200-PAR-2-1-myrpg-pierre.pruvost
** File description:
** init.c
*/

#include <stdlib.h>
#include "sound.h"

sfMusic **init_sounds_array(void)
{
    sfMusic **arr = malloc(sizeof(sfMusic *) * NB_SOUNDS);

    for (int i = 0; i < NB_SOUNDS; ++i) {
        arr[i] = sfMusic_createFromFile(SOUND_PATH[i]);
        sfMusic_setVolume(arr[i], SOUND_VOLUME[i]);
    }
    return arr;
}

void free_sounds(sfMusic **arr)
{
    for (int i = 0; i < NB_SOUNDS; ++i) {
        sfMusic_destroy(arr[i]);
    }
    free(arr);
}
