/*
** EPITECH PROJECT, 2024
** event_menu_file.c
** File description:
** managing event
*/

#include <stdbool.h>

#include "my.h"
#include "game.h"
#include "menus.h"

static void display_menu(sfRenderWindow *window, sprite_t *sprites)
{
    sfRenderWindow_clear(window, BG_DEFAULT_COLOR);
    sfRenderWindow_drawSprite(window, sprites[HEROES_BCKG].sprite, NULL);
    sfRenderWindow_drawSprite(window, sprites[SELECT].sprite, NULL);
    sfRenderWindow_drawSprite(window, sprites[IDLE_FIRE_KNIGHT].sprite, NULL);
    sfRenderWindow_drawSprite(window,
        sprites[IDLE_WIZARD_WANDERER].sprite, NULL);
    sfRenderWindow_drawSprite(window,
        sprites[IDLE_NINJA_PEASANT].sprite, NULL);
    sfRenderWindow_display(window);
}

static bool is_in_hero(sfVector2i pos, int k)
{
    int resx = pos.x - (int)(SELECTOR_POS.x + SELECTOR_OFST.x * k);
    int resy = pos.y - (int)(SELECTOR_POS.y);

    if (resx <= SELECTOR_OFST.x && resx >= 0 &&
        resy <= HERO_HEIGHT && resy >= 0)
        return true;
    return false;
}

static int manage_menu_click(display_t *display, sprite_t *sprites,
    sfVector2i pos, int *hover)
{
    for (int k = 0; k < NB_HEROES; k++) {
        if (is_in_hero(pos, k) == true)
            return k;
    }
    return UNSELECTED;
}

static void manage_sound_hover(display_t *display, int *hover, int k)
{
    if (*hover != k)
        play_sound(display->sounds[DROP_WAV]);
    *hover = k;
}

static void manage_options_hover(display_t *display, sprite_t *sprites,
    sfVector2i pos, int *hover)
{
    for (int k = 0; k < NB_HEROES; k++) {
        if (is_in_hero(pos, k) == true) {
            sfSprite_setPosition(sprites[SELECT].sprite,
                (sfVector2f){(640 * k) + 130, 880});
            manage_sound_hover(display, hover, k);
            return;
        }
    }
    *hover = UNSELECTED;
    sfSprite_setPosition(sprites[SELECT].sprite, (sfVector2f){-1000, -1000});
}

static int manage_menu_events(display_t *display, sprite_t *sprites,
    int *hover)
{
    sfEvent event;
    int res = UNSELECTED;
    sfVector2i pos;

    while (sfRenderWindow_pollEvent(display->window, &event)) {
        pos = sfMouse_getPosition((sfWindow *)display->window);
        manage_options_hover(display, sprites, pos, hover);
        if (event.type == sfEvtClosed)
            sfRenderWindow_close(display->window);
        if (event.type == sfEvtMouseButtonPressed)
            res = manage_menu_click(display, sprites, pos, hover);
        if (res != UNSELECTED)
            return res;
    }
    return res;
}

int hero_selection(display_t *display, sprite_t *sprites)
{
    sfClock *clock;
    int hover = UNSELECTED;
    int res = UNSELECTED;

    while (sfRenderWindow_isOpen(display->window) && res == UNSELECTED) {
        res = manage_menu_events(display, sprites, &hover);
        display_menu(display->window, sprites);
    }
    return res;
}
