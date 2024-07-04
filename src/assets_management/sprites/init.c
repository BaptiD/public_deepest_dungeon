/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** sprites/init.c
*/

#include "game.h"
#include "sprites.h"
#include "my.h"

static void init_sprites_params(sprite_t *sprites)
{
    sfColor color = {255, 255, 255, 150};

    logs(INFO, "Sprites specific parameters initialization...");
    sfSprite_setColor(sprites[COVER].sprite, color);
    for (int k = 0; k < SIZE_TAB; k++)
        sfSprite_setTextureRect(sprites[k].sprite, get_rect(k, 0));
    sfSprite_setOrigin(sprites[ITEM_HINT].sprite,
        (sfVector2f){RESIZE[ITEM_HINT].x / 2, RESIZE[ITEM_HINT].y / 2});
    sfSprite_setOrigin(sprites[MEMBER_DRAG_HINT].sprite,
        (sfVector2f){RESIZE[MEMBER_DRAG_HINT].x / 2,
            RESIZE[MEMBER_DRAG_HINT].y / 2});
    sfSprite_setColor(sprites[MEMBER_DRAG_HINT].sprite, HINT_COLOR);
    logs(SUCCESS, "Sprites specific parameters initialized");
}

sprite_t *init_spritesarray(void)
{
    sprite_t *sprites = malloc(sizeof(sprite_t) * SIZE_TAB);
    sprite_t temp;
    sfVector2f size;

    logs(INFO, "Sprites initialization...");
    for (int k = 0; k < SIZE_TAB; k++) {
        temp.sprite = sfSprite_create();
        temp.texture = sfTexture_createFromFile(IMG_PATH[k], NULL);
        sfSprite_setPosition(temp.sprite, POSITION[k]);
        sfSprite_setTexture(temp.sprite, temp.texture, sfTrue);
        size.x = RESIZE[k].x / IMG_SIZE[k].x;
        size.y = RESIZE[k].y / IMG_SIZE[k].y;
        sfSprite_scale(temp.sprite, size);
        sprites[k] = temp;
    }
    logs(SUCCESS, "Sprites initialized");
    init_sprites_params(sprites);
    return sprites;
}
