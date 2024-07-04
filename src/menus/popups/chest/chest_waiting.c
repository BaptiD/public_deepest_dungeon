/*
** EPITECH PROJECT, 2024
** event_menu_file.c
** File description:
** managing event
*/

#include "entity.h"
#include "game.h"
#include "sprites.h"
#include "items.h"

static void display_indication(display_t *display, sfText *text)
{
    sfVector2f pos = {1800, 900};

    sfText_setCharacterSize(text, 30);
    sfText_setString(text, "Press [SPACE] to open");
    pos.x -= sfText_getLocalBounds(text).width;
    sfText_setPosition(text, pos);
    sfRenderWindow_drawText(display->window, text, NULL);
}

static void display_chest(display_t *display, sfText *text)
{
    sfRenderWindow_clear(display->window, sfBlack);
    display_indication(display, text);
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

static void set_item_sprite(display_t *display, int item)
{
    sfSprite_setScale(display->tab[CHEST_OPENING].sprite, (sfVector2f){4, 4});
    sfSprite_setTextureRect(display->tab[CHEST_OPENING].sprite,
        get_rect(CHEST_OPENING, 0));
    if (item != -1) {
        sfSprite_setPosition(display->tab[ITEM_SPRITE[item]].sprite,
            ITEM_CHEST_START_POS);
    }
}

void chest_opening(display_t *display, int item)
{
    int keep = true;
    sfFont *font = sfFont_createFromFile(MENU_FONT);
    sfText *text = init_text(font, (sfVector2f){0, 0}, sfWhite, 40);

    set_item_sprite(display, item);
    while (keep == true && sfRenderWindow_isOpen(display->window)) {
        display_chest(display, text);
        keep = manage_popup_events(display);
    }
    anim_chest_opening(display, text, item);
    sfText_destroy(text);
    sfFont_destroy(font);
}
