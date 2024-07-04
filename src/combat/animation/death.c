/*
** EPITECH PROJECT, 2024
** event_menu_file.c
** File description:
** managing event
*/

#include "entity.h"
#include "game.h"
#include "sprites.h"
#include "combat.h"

static void display_you_died(display_t *display, sfText *text, int anim)
{
    int limit = anim - 40;
    char *message = "YOU DIED.";
    char actual[limit + 1];
    sfVector2f pos = {960, 450};

    if (limit > 9)
        limit = 9;
    for (int k = 0; k < limit && message[k] != 0; k++)
        actual[k] = message[k];
    actual[limit] = 0;
    sfText_setString(text, actual);
    pos.x -= sfText_getLocalBounds(text).width / 2;
    sfText_setPosition(text, pos);
    sfRenderWindow_drawText(display->window, text, NULL);
}

static void display_death(display_t *display, sfText *text, int anim)
{
    sfRenderWindow_clear(display->window, sfBlack);
    display_you_died(display, text, anim);
    if (anim == 55) {
        sfRenderWindow_drawSprite(display->window,
            display->tab[BACK_TO_LOBBY].sprite, NULL);
    }
    sfRenderWindow_display(display->window);
}

static bool manage_mouse_click(sfVector2i pos, display_t *display)
{
    if (is_in_hitbox(pos, BACK_TO_LOBBY) == true) {
        play_sound(display->sounds[CLICK_WAV]);
        return false;
    }
    return true;
}

static void manage_hover(sfVector2i pos, display_t *display, int *hover)
{
    if (is_in_hitbox(pos, BACK_TO_LOBBY) == true) {
        if (*hover == false) {
            play_sound(display->sounds[DROP_WAV]);
            *hover = true;
        }
        sfSprite_setTextureRect(display->tab[BACK_TO_LOBBY].sprite,
            get_rect(BACK_TO_LOBBY, 1));
    } else {
        *hover = false;
        sfSprite_setTextureRect(display->tab[BACK_TO_LOBBY].sprite,
            get_rect(BACK_TO_LOBBY, 0));
    }
}

static bool manage_popup_events(display_t *display, int *hover)
{
    sfEvent event;
    sfVector2i pos = sfMouse_getPosition((sfWindow *)display->window);

    while (sfRenderWindow_pollEvent(display->window, &event)) {
        manage_hover(pos, display, hover);
        if (event.type == sfEvtClosed)
            sfRenderWindow_close(display->window);
        if (event.type == sfEvtMouseButtonPressed)
            return manage_mouse_click(pos, display);
        if (event.type == sfEvtKeyPressed &&
            sfKeyboard_isKeyPressed(sfKeySpace) == true)
            return false;
    }
    return true;
}

static void change_animation(display_t *display, sfClock *clock, int *anim)
{
    sfTime time = sfClock_getElapsedTime(clock);
    float seconds = time.microseconds / 1000000.0;
    sfVector2f pos = DEAD_SCREEN_START;

    if (*anim < 40) {
        if (seconds > 0.06) {
            *anim += 1;
            sfClock_restart(clock);
            sfRenderWindow_drawSprite(display->window,
                display->tab[COVER].sprite, NULL);
            sfRenderWindow_display(display->window);
        }
    }
    if (*anim >= 40 && *anim < 55) {
        if (seconds > 0.2) {
            *anim += 1;
            if (*anim < 50)
                play_sound(display->sounds[KEY_PRESS_WAV]);
            sfClock_restart(clock);
        }
    }
}

void display_death_player(display_t *display, entity_t *player, int player_pos)
{
    int keep = true;
    int anim = 0;
    int hover = false;
    sfClock *clock = sfClock_create();
    sfFont *font = sfFont_createFromFile(MENU_FONT);
    sfText *text = init_text(font, (sfVector2f){0, 0}, sfRed, 70);

    while (keep == 1 && sfRenderWindow_isOpen(display->window)) {
        change_animation(display, clock, &anim);
        if (anim > 40)
            display_death(display, text, anim);
        keep = manage_popup_events(display, &hover);
    }
    sfSprite_setTextureRect(display->tab[BACK_TO_LOBBY].sprite,
            get_rect(BACK_TO_LOBBY, 0));
}
