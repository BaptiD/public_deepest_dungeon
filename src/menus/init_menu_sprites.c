/*
** EPITECH PROJECT, 2024
** event_menu_file.c
** File description:
** managing event
*/

#include <stdbool.h>
#include <stdlib.h>
#include "menus.h"
#include "sprites.h"


static void init_sprites_params(sprite_t *sprites)
{
    sfColor color = {255, 255, 255, 150};

    for (int k = IDLE_FIRE_KNIGHT; k <= IDLE_NINJA_PEASANT; k++) {
        sfSprite_setTextureRect(sprites[k].sprite, FIRST_RECT[k]);
        sfSprite_setOrigin(sprites[k].sprite,
            (sfVector2f){0, FIRST_RECT[k].height});
    }
    for (int k = START_GAME; k <= QUIT_GAME; k++)
        sfSprite_setTextureRect(sprites[k].sprite, FIRST_RECT[k]);
    sfSprite_setTextureRect(sprites[LOAD_SAVE].sprite, FIRST_RECT[LOAD_SAVE]);
    sfSprite_setTextureRect(sprites[HELP].sprite, FIRST_RECT[HELP]);
    sfSprite_setTextureRect(sprites[OPTIONS].sprite, FIRST_RECT[OPTIONS]);
    sfSprite_setTextureRect(sprites[BACK].sprite, FIRST_RECT[BACK]);
    sfSprite_setTextureRect(sprites[BACK].sprite, FIRST_RECT[BACK]);
    sfSprite_setTextureRect(sprites[MAIN_MENU].sprite, FIRST_RECT[MAIN_MENU]);
    sfSprite_setTextureRect(sprites[RED_CROSS].sprite, FIRST_RECT[RED_CROSS]);
    sfSprite_setTextureRect(sprites[SPEAKER_ON].sprite, FIRST_RECT[SPEAKER_ON]);
    sfSprite_setTextureRect(sprites[SPEAKER_OFF].sprite, FIRST_RECT[SPEAKER_OFF]);
    sfSprite_setTextureRect(sprites[DRAG_BALL].sprite, FIRST_RECT[DRAG_BALL]);
}

sprite_t *init_menu_sprites(void)
{
    sprite_t *sprites = malloc(sizeof(sprite_t) * NB_MENU_IMG);
    sprite_t temp;
    sfVector2f size;

    for (int k = 0; k < NB_MENU_IMG; k++) {
        temp.sprite = sfSprite_create();
        temp.texture = sfTexture_createFromFile(MENU_IMG_PATH[k], NULL);
        sfSprite_setPosition(temp.sprite, MENU_IMG_POSITION[k]);
        sfSprite_setTexture(temp.sprite, temp.texture, sfTrue);
        size.x = MENU_IMG_RESIZE[k].x / MENU_IMG_SIZE[k].x;
        size.y = MENU_IMG_RESIZE[k].y / MENU_IMG_SIZE[k].y;
        sfSprite_scale(temp.sprite, size);
        sprites[k] = temp;
    }
    init_sprites_params(sprites);
    return sprites;
}
