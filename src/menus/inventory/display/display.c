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

void display_inventory(display_t *display, entity_t *player, sfText *text,
    int *selection)
{
    sfRenderWindow_drawSprite(display->window,
        display->tab[INVENTORY_BG].sprite, NULL);
    display_selection(display, player, text, selection);
    display_buttons(display, player, selection);
    display_items(display, player, text, selection);
    display_squad(display, player, text, selection);
}
