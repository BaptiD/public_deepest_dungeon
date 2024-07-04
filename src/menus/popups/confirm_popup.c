/*
** EPITECH PROJECT, 2024
** event_menu_file.c
** File description:
** managing event
*/

#include "entity.h"
#include "game.h"
#include "sprites.h"

static void display_popup(display_t *display, entity_t *player, int *selection,
    sfText *text)
{
    sfRenderWindow *window = display->window;
    sprite_t *sprites = display->tab;

    sfRenderWindow_drawSprite(window, sprites[CONFIRM_POPUP].sprite, NULL);
    sfRenderWindow_drawSprite(window, sprites[PROCEED].sprite, NULL);
    sfRenderWindow_drawSprite(window, sprites[CANCEL].sprite, NULL);
}

static void manage_button_hover(sfRenderWindow *window, sprite_t *sprites,
    int k)
{
    sfIntRect rect;
    sfVector2i pos = sfMouse_getPosition((sfWindow *)window);

    if (is_in_hitbox(pos, k) == 1) {
        rect = get_rect(k, 1);
        sfSprite_setTextureRect(sprites[k].sprite, rect);
    } else {
        rect = get_rect(k, 0);
        sfSprite_setTextureRect(sprites[k].sprite, rect);
    }
}

static int still_in_popup(sfVector2i pos)
{
    int resx = pos.x - POSITION[CONFIRM_POPUP].x;
    int resy = pos.y - POSITION[CONFIRM_POPUP].y;

    if (resx < RESIZE[CONFIRM_POPUP].x && resx > 0)
        if (resy < RESIZE[CONFIRM_POPUP].y && resy > 0)
            return 1;
    return 0;
}

static int find_click(sfVector2i pos, int *run, sprite_t *sprites)
{
    sfIntRect rect;

    if (still_in_popup(pos) == 0)
        return -1;
    if (is_in_hitbox(pos, CANCEL) == 1)
        return -1;
    if (is_in_hitbox(pos, PROCEED) == 1) {
        rect = get_rect(PROCEED, 2);
        sfSprite_setTextureRect(sprites[PROCEED].sprite, rect);
        return true;
    }
    return false;
}

static void manage_popup_click(sfRenderWindow *window, sprite_t *sprites,
    int *run)
{
    sfIntRect rect;
    sfVector2i pos = sfMouse_getPosition((sfWindow *)window);

    *run = find_click(pos, run, sprites);
}

static void manage_keyboard_click(int *run)
{
    if (sfKeyboard_isKeyPressed(sfKeyEscape) == sfTrue)
        *run = -1;
    if (sfKeyboard_isKeyPressed(sfKeyReturn) == sfTrue)
        *run = true;
}

static char *manage_popup_events(display_t *display, int *run)
{
    sfEvent event;

    while (sfRenderWindow_pollEvent(display->window, &event)) {
        manage_button_hover(display->window, display->tab, PROCEED);
        manage_button_hover(display->window, display->tab, CANCEL);
        if (event.type == sfEvtClosed)
            sfRenderWindow_close(display->window);
        if (event.type == sfEvtMouseButtonPressed)
            manage_popup_click(display->window, display->tab, run);
        if (event.type == sfEvtKeyPressed)
            manage_keyboard_click(run);
    }
}

int confirmation(display_t *display, entity_t *player, int *selection)
{
    int res = false;
    sfFont *font = sfFont_createFromFile(MENU_FONT);
    sfText *text = init_text(font, (sfVector2f){0, 0}, sfWhite, 25);

    sfRenderWindow_drawSprite(display->window, display->tab[COVER].sprite,
        NULL);
    while (res == false && sfRenderWindow_isOpen(display->window)) {
        manage_popup_events(display, &res);
        display_popup(display, player, selection, text);
        sfRenderWindow_display(display->window);
    }
    return res;
}
