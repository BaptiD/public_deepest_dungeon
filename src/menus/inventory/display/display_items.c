/*
** EPITECH PROJECT, 2024
** event_menu_file.c
** File description:
** managing event
*/

#include <stdbool.h>
#include <stdio.h>
#include <math.h>

#include "my.h"
#include "game.h"
#include "entity.h"
#include "items.h"
#include "inventory.h"

void display_items(display_t *display, entity_t *player, sfText *text,
    int *selection)
{
    sfSprite *temp;

    for (int k = 0; k < INVENTORY_SIZE; k++) {
        if (player->inventory[k] != EMPTY) {
            temp = display->tab[ITEM_SPRITE[player->inventory[k]]].sprite;
            sfSprite_setScale(temp, FULL_SIZE);
            sfSprite_setPosition(temp, ITEM_POS[k]);
            sfRenderWindow_drawSprite(display->window, temp, NULL);
        }
    }
}
