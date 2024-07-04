/*
** EPITECH PROJECT, 2024
** event_menu_file.c
** File description:
** managing event
*/

#include <stdio.h>

#include "entity.h"
#include "game.h"
#include "sprites.h"
#include "items.h"

static void display_indication(display_t *display, sfText *text)
{
    sfVector2f pos = {1800, 900};

    sfText_setCharacterSize(text, 30);
    sfText_setString(text, "Press [SPACE] to close");
    pos.x -= sfText_getLocalBounds(text).width;
    sfText_setPosition(text, pos);
    sfRenderWindow_drawText(display->window, text, NULL);
}

static void display_stats_title(display_t *display, sfText *text)
{
    sfVector2f pos = {100, 850};

    sfText_setCharacterSize(text, 30);
    sfText_setString(text, "Item stats :");
    sfText_setPosition(text, pos);
    sfRenderWindow_drawText(display->window, text, NULL);
}

static void display_item_name(display_t *display, sfText *text, int item)
{
    char str[256];
    sfVector2f pos = CHEST_OPEN_ITEM_NAME;

    display_indication(display, text);
    sfText_setCharacterSize(text, 40);
    if (item != -1)
        sprintf(str, "Congratulations, you obtained the %s", ITEM_NAME[item]);
    else
        sprintf(str, "Unlucky, this chest was empty...\n");
    sfText_setString(text, str);
    pos.x -= sfText_getLocalBounds(text).width / 2.0;
    sfText_setPosition(text, pos);
    sfRenderWindow_drawText(display->window, text, NULL);
}

static void display_chest(display_t *display, sfText *text, int item)
{
    sfRenderWindow_clear(display->window, sfBlack);
    display_item_name(display, text, item);
    if (item != -1) {
        sfRenderWindow_drawSprite(display->window,
            display->tab[ITEM_SPRITE[item]].sprite, NULL);
        display_stats_title(display, text);
        display_part_stats(display, text, ITEM_STATS[item],
            OBTAINED_ITEM_STATS_POS);
    }
    sfRenderWindow_drawSprite(display->window,
        display->tab[CHEST_OPENING].sprite, NULL);
    sfRenderWindow_display(display->window);
}

static bool manage_popup_events(display_t *display)
{
    sfEvent event;

    while (sfRenderWindow_pollEvent(display->window, &event)) {
        if (event.type == sfEvtClosed)
            sfRenderWindow_close(display->window);
        if (event.type == sfEvtKeyPressed &&
            sfKeyboard_isKeyPressed(sfKeySpace) == true)
            return false;
    }
    return true;
}

static void set_sprites(display_t *display, int item)
{
    if (item != -1) {
        sfSprite_setScale(display->tab[ITEM_SPRITE[item]].sprite,
            (sfVector2f){1.86, 1.86});
        sfSprite_setPosition(display->tab[ITEM_SPRITE[item]].sprite,
            (sfVector2f){867, 500});
    }
    sfSprite_setTextureRect(display->tab[CHEST_OPENING].sprite,
        get_rect(CHEST_OPENING, 3));
}

void display_chest_obtained(display_t *display, sfText *text, int item)
{
    int keep = true;
    int animation = 0;

    set_sprites(display, item);
    while (keep == 1 && sfRenderWindow_isOpen(display->window)) {
        display_chest(display, text, item);
        keep = manage_popup_events(display);
    }
}
