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
#include "sound.h"
#include "options.h"

static void display_ball_music(display_t *display, sprite_t *sprites)
{
    double vol_music = 0;
    sfVector2f pos = {0};
    sfVector2i mouse_pos = sfMouse_getPosition((sfWindow *)display->window);

    if (sfMusic_getVolume(display->sounds[0]) == 0)
        vol_music = 0;
    else
        vol_music = sfMusic_getVolume(display->sounds[0]) / 15;
    pos = (sfVector2f){START_BALL + ((END_BALL - START_BALL) * vol_music),
        BALL_Y[0]};
    if (is_in_zone(mouse_pos, pos, BALL_SIZE) == true)
        sfSprite_setTextureRect(sprites[DRAG_BALL].sprite,
            get_rect_menu(DRAG_BALL, 1));
    else
        sfSprite_setTextureRect(sprites[DRAG_BALL].sprite,
            get_rect_menu(DRAG_BALL, 0));
    sfSprite_setPosition(sprites[DRAG_BALL].sprite, pos);
    sfRenderWindow_drawSprite(display->window,
        sprites[DRAG_BALL].sprite, NULL);
}

static void display_ball_effects(display_t *display, sprite_t *sprites)
{
    double vol_effects = 0;
    sfVector2f pos = {0};
    sfVector2i mouse_pos = sfMouse_getPosition((sfWindow *)display->window);

    if (sfMusic_getVolume(display->sounds[2]) == 0)
        vol_effects = 0;
    else
        vol_effects = sfMusic_getVolume(display->sounds[2]) / 30;
    pos = (sfVector2f){START_BALL + ((END_BALL - START_BALL) * vol_effects),
        BALL_Y[1]};
    if (is_in_zone(mouse_pos, pos, BALL_SIZE) == true)
        sfSprite_setTextureRect(sprites[DRAG_BALL].sprite,
            get_rect_menu(DRAG_BALL, 1));
    else
        sfSprite_setTextureRect(sprites[DRAG_BALL].sprite,
            get_rect_menu(DRAG_BALL, 0));
    sfSprite_setPosition(sprites[DRAG_BALL].sprite, pos);
    sfRenderWindow_drawSprite(display->window,
        sprites[DRAG_BALL].sprite, NULL);
}

static int display_speaker_on(display_t *display, sprite_t *sprites,
    int *hover, int n)
{
    sfVector2i pos = sfMouse_getPosition((sfWindow *)display->window);
    sfSprite *sprite = sprites[SPEAKER_ON].sprite;

    if (is_in_zone(pos, SPEAKER_ON_POS[n],
        MENU_IMG_RESIZE[SPEAKER_ON]) == true) {
        sfSprite_setTextureRect(sprite, get_rect_menu(SPEAKER_ON, 1));
        sfSprite_setPosition(sprite, SPEAKER_ON_POS[n]);
        sfRenderWindow_drawSprite(display->window, sprite, NULL);
        return IN;
    } else {
        sfSprite_setTextureRect(sprite, get_rect_menu(SPEAKER_ON, 0));
        sfSprite_setPosition(sprite, SPEAKER_ON_POS[n]);
        sfRenderWindow_drawSprite(display->window, sprite, NULL);
        return OUT;
    }
}

static int display_speaker_off(display_t *display, sprite_t *sprites,
    int *hover, int n)
{
    sfVector2i pos = sfMouse_getPosition((sfWindow *)display->window);
    sfSprite *sprite = sprites[SPEAKER_OFF].sprite;

    if (is_in_zone(pos, SPEAKER_OFF_POS[n],
        MENU_IMG_RESIZE[SPEAKER_OFF]) == true) {
        sfSprite_setTextureRect(sprite, get_rect_menu(SPEAKER_OFF, 1));
        sfSprite_setPosition(sprite, SPEAKER_OFF_POS[n]);
        sfRenderWindow_drawSprite(display->window, sprite, NULL);
        return IN;
    } else {
        sfSprite_setTextureRect(sprite, get_rect_menu(SPEAKER_OFF, 0));
        sfSprite_setPosition(sprite, SPEAKER_OFF_POS[n]);
        sfRenderWindow_drawSprite(display->window, sprite, NULL);
        return OUT;
    }
}

static void display_buttons(display_t *display, sprite_t *sprites, int *hover)
{
    sfRenderWindow *window = display->window;

    for (int k = 0; k < NB_SOUND_BARS; k++) {
        display_speaker_on(display, sprites, hover, k);
        display_speaker_off(display, sprites, hover, k);
    }
    display_ball_music(display, sprites);
    display_ball_effects(display, sprites);
}

void display_options(display_t *display, sprite_t *sprites, int *hover)
{
    sfRenderWindow *window = display->window;

    sfRenderWindow_drawSprite(window, sprites[OPTIONS_BG].sprite, NULL);
    display_buttons(display, sprites, hover);
    sfRenderWindow_drawSprite(window, sprites[RED_CROSS].sprite, NULL);
    sfRenderWindow_display(window);
}
