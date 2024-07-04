/*
** EPITECH PROJECT, 2024
** event_menu_file.c
** File description:
** managing event
*/

#include <stdbool.h>

#include "menus.h"
#include "game.h"
#include "entity.h"
#include "my.h"

static void display_menu(sfRenderWindow *window, sprite_t *sprites)
{
    sfRenderWindow_clear(window, BG_DEFAULT_COLOR);
    sfRenderWindow_drawSprite(window, sprites[HELP_POP].sprite, NULL);
    sfRenderWindow_drawSprite(window, sprites[RED_CROSS].sprite, NULL);
    sfRenderWindow_display(window);
}

static int manage_menu_click(display_t *display, sprite_t *sprites)
{
    sfVector2i pos = sfMouse_getPosition((sfWindow *)display->window);

    if (is_in_hitbox_menu(pos, RED_CROSS) == true) {
        play_sound(display->sounds[CLICK_WAV]);
        return false;
    }
    return true;
}

static int manage_button_hover(display_t *display, sprite_t *sprites,
    int k, int *hover)
{
    sfIntRect rect;
    sfVector2i pos = sfMouse_getPosition((sfWindow *)display->window);

    if (is_in_hitbox_menu(pos, k) == 1) {
        if (*hover == OUT)
            play_sound(display->sounds[DROP_WAV]);
        rect = get_rect_menu(k, 1);
        sfSprite_setTextureRect(sprites[k].sprite, rect);
        return IN;
    } else {
        rect = get_rect_menu(k, 0);
        sfSprite_setTextureRect(sprites[k].sprite, rect);
        return OUT;
    }
}

static void manage_options_hover(display_t *display, sprite_t *sprites,
    int *hover)
{
    *hover = manage_button_hover(display, sprites, RED_CROSS, hover);
}

static int manage_menu_events(display_t *display, sprite_t *sprites,
    int *hover)
{
    sfEvent event;
    int menu = true;

    while (sfRenderWindow_pollEvent(display->window, &event)) {
        manage_options_hover(display, sprites, hover);
        if (event.type == sfEvtClosed)
            sfRenderWindow_close(display->window);
        if (event.type == sfEvtKeyPressed &&
            sfKeyboard_isKeyPressed(sfKeyEscape) == true)
            return false;
        if (event.type == sfEvtMouseButtonPressed)
            menu = manage_menu_click(display, sprites);
        if (menu == false)
            return menu;
    }
    return menu;
}

void help_popup(display_t *display, sprite_t *sprites)
{
    int menu = true;
    int hover = OUT;

    play_sound(display->sounds[CLICK_WAV]);
    while (sfRenderWindow_isOpen(display->window) && menu == true) {
        menu = manage_menu_events(display, sprites, &hover);
        display_menu(display->window, sprites);
    }
    sfSprite_setTextureRect(sprites[RED_CROSS].sprite, get_rect_menu(RED_CROSS, 0));
}
