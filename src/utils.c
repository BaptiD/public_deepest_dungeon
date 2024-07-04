/*
** EPITECH PROJECT, 2024
** my_hunter.c
** File description:
** my hunter game
*/

#include <SFML/Graphics.h>
#include <SFML/Audio.h>
#include <stdbool.h>
#include "my.h"
#include "sprites.h"

sfText *init_text(sfFont *font, sfVector2f pos, sfColor color, int size)
{
    sfText *text = sfText_create();

    sfText_setColor(text, color);
    sfText_setPosition(text, pos);
    sfText_setFont(text, font);
    sfText_setCharacterSize(text, size);
    return text;
}

int is_in_hitbox(sfVector2i pos, int index)
{
    int resx = pos.x - POSITION[index].x;
    int resy = pos.y - POSITION[index].y;

    if (resx < RESIZE[index].x && resx > 0)
        if (resy < RESIZE[index].y && resy > 0)
            return true;
    return false;
}

sfVector2f combine_vectors(sfVector2f vect1, sfVector2f vect2)
{
    return (sfVector2f){vect1.x + vect2.x, vect1.y + vect2.y};
}

int is_in_zone(sfVector2i pos, sfVector2f zone, sfVector2f zone_size)
{
    int resx = pos.x - zone.x;
    int resy = pos.y - zone.y;

    if (resx >= 0 && resx <= zone_size.x)
        if (resy >= 0 && resy <= zone_size.y)
            return true;
    return false;
}