/*
** EPITECH PROJECT, 2024
** display_entitites
** File description:
** functions to display player/pnjs in game rpg
*/

#include "entity.h"
#include "game.h"

sfIntRect display_entity(sfRenderWindow *window, sfClock *clock,
    sprite_t *display, sfIntRect rect)
{
    sfTime time;

    time = sfClock_getElapsedTime(clock);
    if (time.microseconds > 500000) {
        if (rect.left + 32 > 96)
            rect.left = 0;
        else
            rect.left += 32;
        sfSprite_setTextureRect(display->sprite,
            rect);
        sfClock_restart(clock);
    }
    sfRenderWindow_drawSprite(window, display->sprite,
        NULL);
    return rect;
}
