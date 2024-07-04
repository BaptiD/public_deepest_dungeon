/*
** EPITECH PROJECT, 2023
** my_rpg
** File description:
** get_rect.c
*/

#include <SFML/Graphics.h>
#include "sprites.h"

sfIntRect get_rect(int index, int offset)
{
    sfIntRect rect;

    rect.left = IMG_SIZE[index].x * offset;
    rect.top = 0;
    rect.width = IMG_SIZE[index].x;
    rect.height = IMG_SIZE[index].y;
    return rect;
}
