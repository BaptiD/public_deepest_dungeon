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

static void display_text_hint(display_t *display, sfText *text,
    int before, int buff)
{
    sfVector2i pos = sfMouse_getPosition((sfWindow *)display->window);
    int size_text = 0;
    char str[256];

    sfText_setColor(text, sfGreen);
    sprintf(str, "%i --> %i", before, before + buff);
    sfText_setString(text, str);
    size_text = (int)sfText_getLocalBounds(text).width;
    sfText_setPosition(text, (sfVector2f){pos.x, pos.y - 27});
    sfSprite_setScale(display->tab[UPGRADE_HINT].sprite,
        (sfVector2f){(size_text + 13) / RESIZE[UPGRADE_HINT].x, 1.2});
    sfSprite_setPosition(display->tab[UPGRADE_HINT].sprite,
        (sfVector2f){pos.x - 5, pos.y - 30});
    sfRenderWindow_drawSprite(display->window,
        display->tab[UPGRADE_HINT].sprite, NULL);
    sfRenderWindow_drawText(display->window, text, NULL);
    sfText_setColor(text, sfBlack);
}

static void display_hint(display_t *display, entity_t *player, sfText *text,
    entity_t *upgrading)
{
    sfVector2i pos = sfMouse_getPosition((sfWindow *)display->window);

    if (is_in_hitbox(pos, BUT_ATTACK) == true)
        return display_text_hint(display, text, upgrading->stats->atk, UP_ATK);
    if (is_in_hitbox(pos, BUT_HEALTH) == true)
        return display_text_hint(display, text, upgrading->stats->hp, UP_HP);
    if (is_in_hitbox(pos, BUT_SPEED) == true)
        return display_text_hint(display, text, upgrading->stats->spd, UP_SPD);
    if (is_in_hitbox(pos, BUT_PRECISION) == true)
        return display_text_hint(display, text, upgrading->stats->pre, UP_PRE);
    if (is_in_hitbox(pos, BUT_CRITIC) == true)
        return display_text_hint(display, text, upgrading->stats->crt, UP_CRT);
}

static void display_popup(display_t *display, entity_t *player, sfText *text,
    entity_t *upgrading)
{
    sfRenderWindow *window = display->window;
    sprite_t *sprites = display->tab;
    int text_x = 0;

    sfRenderWindow_clear(window, BG_DEFAULT_COLOR);
    sfRenderWindow_drawSprite(window, sprites[BACKGROUND].sprite, NULL);
    sfRenderWindow_drawSprite(window, sprites[COVER].sprite, NULL);
    sfRenderWindow_drawSprite(window, sprites[UP_POPUP].sprite, NULL);
    sfText_setColor(text, sfRed);
    sfText_setString(text, upgrading->name);
    sfText_setCharacterSize(text, 48);
    text_x = (1920 / 2) - ((int)sfText_getLocalBounds(text).width / 2);
    sfText_setPosition(text, (sfVector2f){text_x, 296});
    sfRenderWindow_drawText(window, text, NULL);
    sfText_setColor(text, sfBlack);
    sfText_setCharacterSize(text, 25);
    for (int k = BUT_ATTACK; k <= BUT_CRITIC; k++)
        sfRenderWindow_drawSprite(window, sprites[k].sprite, NULL);
    display_hint(display, player, text, upgrading);
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

static int find_click(sfVector2i pos, sprite_t *sprites)
{
    sfIntRect rect;

    if (is_in_hitbox(pos, BUT_ATTACK) == true)
        return ATK;
    if (is_in_hitbox(pos, BUT_HEALTH) == true)
        return HP;
    if (is_in_hitbox(pos, BUT_SPEED) == true)
        return SPD;
    if (is_in_hitbox(pos, BUT_PRECISION) == true)
        return PRE;
    if (is_in_hitbox(pos, BUT_CRITIC) == true)
        return CRT;
    return -1;
}

static void manage_popup_click(sfRenderWindow *window, sprite_t *sprites,
    int *run)
{
    sfIntRect rect;
    sfVector2i pos = sfMouse_getPosition((sfWindow *)window);

    *run = find_click(pos, sprites);
}

static char *manage_popup_events(display_t *display, int *run)
{
    sfEvent event;

    while (sfRenderWindow_pollEvent(display->window, &event)) {
        manage_button_hover(display->window, display->tab, BUT_ATTACK);
        manage_button_hover(display->window, display->tab, BUT_HEALTH);
        manage_button_hover(display->window, display->tab, BUT_SPEED);
        manage_button_hover(display->window, display->tab, BUT_PRECISION);
        manage_button_hover(display->window, display->tab, BUT_CRITIC);
        if (event.type == sfEvtClosed)
            sfRenderWindow_close(display->window);
        if (event.type == sfEvtMouseButtonPressed)
            manage_popup_click(display->window, display->tab, run);
    }
}

int chose_stat(display_t *display, entity_t *player, entity_t *upgrading)
{
    int res = -1;
    sfFont *font = sfFont_createFromFile(MENU_FONT);
    sfText *text = init_text(font, (sfVector2f){900, 425}, sfBlack, 25);
    int text_x = 0;

   
    while (res == -1 && sfRenderWindow_isOpen(display->window)) {
        manage_popup_events(display, &res);
        display_popup(display, player, text, upgrading);
        sfRenderWindow_display(display->window);
    }
    sfText_destroy(text);
    sfFont_destroy(font);
    return res;
}
