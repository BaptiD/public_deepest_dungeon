/*
** EPITECH PROJECT, 2024
** event_menu_file.c
** File description:
** managing event
*/

#include <stdbool.h>
#include <stdio.h>

#include "my.h"
#include "game.h"
#include "entity.h"
#include "items.h"
#include "inventory.h"

static bool manage_menu_click(display_t *display, entity_t *player,
    int *selection)
{
    sfVector2i pos = sfMouse_getPosition((sfWindow *)display->window);

    if (pos.x < 500) {
        manage_click_items(display, player, selection, pos);
    } else {
        if (pos.y < 765)
            manage_click_members(display, player, selection, pos);
        else
            manage_click_spells(display, player, selection, pos);
    }
    return true;
}

static bool switch_selection(int *selection, int index, int new)
{
    if (selection[index] == new)
        selection[index] = OFF;
    else
        selection[index] = new;
    return true;
}

static bool manage_keyboard_click(display_t *display, entity_t *player,
    int *selection)
{
    if (sfKeyboard_isKeyPressed(sfKeyTab))
        return false;
    if (sfKeyboard_isKeyPressed(sfKeyEscape))
        return false;
    if (sfKeyboard_isKeyPressed(sfKeyA))
        return switch_selection(selection, SPELL_SELECT, 0);
    if (sfKeyboard_isKeyPressed(sfKeyZ))
        return switch_selection(selection, SPELL_SELECT, 1);
    if (sfKeyboard_isKeyPressed(sfKeyE))
        return switch_selection(selection, SPELL_SELECT, 2);
    if (sfKeyboard_isKeyPressed(sfKeyR))
        return switch_selection(selection, SPELL_SELECT, 3);
    return true;
}

static int manage_menu_events(display_t *display, entity_t *player,
    int *selection)
{
    sfEvent event;
    int menu = true;

    while (sfRenderWindow_pollEvent(display->window, &event)) {
        if (event.type == sfEvtClosed) {
            sfRenderWindow_close(display->window);
            return false;
        }
        if (event.type == sfEvtMouseButtonPressed)
            menu = manage_menu_click(display, player, selection);
        if (event.type == sfEvtKeyPressed)
            menu = manage_keyboard_click(display, player, selection);
        if (menu == false)
            return false;
    }
    return menu;
}

void inventory(display_t *display, entity_t *player)
{
    bool menu = true;
    int selection[3] = {OFF, OFF, OFF};
    sfFont *font = sfFont_createFromFile(MENU_FONT);
    sfText *text = init_text(font, (sfVector2f){0, 0}, sfWhite, 25);

    while (sfRenderWindow_isOpen(display->window) && menu == true) {
        display_inventory(display, player, text, selection);
        sfRenderWindow_display(display->window);
        menu = manage_menu_events(display, player, selection);
    }
    sfText_destroy(text);
    sfFont_destroy(font);
}
