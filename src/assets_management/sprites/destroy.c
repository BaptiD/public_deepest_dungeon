/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** sprites/destroy.c
*/

#include "my.h"
#include "game.h"
#include "sprites.h"

void destroy_sprites(sprite_t *sprites, int len)
{
    for (int k = 0; k < len; k++) {
        sfSprite_destroy(sprites[k].sprite);
        sfTexture_destroy(sprites[k].texture);
    }
    free(sprites);
}
