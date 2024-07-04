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
    sfRenderWindow_drawSprite(window, sprites[IG_MENU_BCKG].sprite, NULL);
    sfRenderWindow_drawSprite(window, sprites[BACK].sprite, NULL);
    sfRenderWindow_drawSprite(window, sprites[OPTIONS].sprite, NULL);
    sfRenderWindow_drawSprite(window, sprites[HELP].sprite, NULL);
    sfRenderWindow_drawSprite(window, sprites[MAIN_MENU].sprite, NULL);
    sfRenderWindow_display(window);
}

static int manage_menu_click(display_t *display, sprite_t *sprites,
    int *run_game)
{
    sfVector2i pos = sfMouse_getPosition((sfWindow *)display->window);

    if (is_in_hitbox_menu(pos, BACK) == true) {
        play_sound(display->sounds[CLICK_WAV]);
        return false;
    }
    if (is_in_hitbox_menu(pos, MAIN_MENU) == true) {
        play_sound(display->sounds[CLICK_WAV]);
        *run_game = false;
        return false;
    }
    if (is_in_hitbox_menu(pos, OPTIONS) == true) {
        play_sound(display->sounds[CLICK_WAV]);
        options(display, sprites);
    }
    if (is_in_hitbox_menu(pos, HELP) == true)
        help_popup(display, sprites);
    return true;
}

static int manage_button_hover(display_t *display, sprite_t *sprites,
    int k, int *hover)
{
    sfVector2i pos = sfMouse_getPosition((sfWindow *)display->window);
    sfIntRect rect;

    if (is_in_hitbox_menu(pos, k) == true) {
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
    int buttons = OUT;

    if (manage_button_hover(display, sprites, BACK, hover) == IN)
        buttons = IN;
    if (manage_button_hover(display, sprites, MAIN_MENU, hover) == IN)
        buttons = IN;
    if (manage_button_hover(display, sprites, OPTIONS, hover) == IN)
        buttons = IN;
    if (manage_button_hover(display, sprites, HELP, hover) == IN)
        buttons = IN;
    if (buttons == OUT)
        *hover = OUT;
    else
        *hover = IN;
}

static int manage_menu_events(display_t *display, sprite_t *sprites,
    int *hover, int *run_game)
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
            menu = manage_menu_click(display, sprites, run_game);
        if (menu == false)
            return menu;
    }
    return menu;
}

void pause_menu(display_t *display, int *run_game)
{
    int menu = true;
    sprite_t *sprites = init_menu_sprites();
    int hover = OUT;

    play_sound(display->sounds[CLICK_WAV]);
    while (sfRenderWindow_isOpen(display->window) && menu == true) {
        display_menu(display->window, sprites);
        menu = manage_menu_events(display, sprites, &hover, run_game);
    }
    destroy_sprites(sprites, NB_MENU_IMG);
}
