/*
** EPITECH PROJECT, 2024
** B-MUL-200-PAR-2-1-myrpg-pierre.pruvost
** File description:
** init_game.c
*/

#include "game.h"

display_t *setup_display(sfRenderWindow *window)
{
    display_t *display = malloc(sizeof(display_t));

    display->resolution = (sfVector2f){VIDEOMODE.width, VIDEOMODE.height};
    display->window = window;
    display->tab = init_spritesarray();
    display->sounds = init_sounds_array();
    return display;
}
