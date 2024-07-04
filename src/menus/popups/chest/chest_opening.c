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
    sfText_setString(text, "Press [SPACE] to skip");
    pos.x -= sfText_getLocalBounds(text).width;
    sfText_setPosition(text, pos);
    sfRenderWindow_drawText(display->window, text, NULL);
}

static void display_chest(display_t *display, sfText *text, int item)
{
    sfRenderWindow_clear(display->window, sfBlack);
    display_indication(display, text);
    if (item != -1) {
        sfRenderWindow_drawSprite(display->window,
            display->tab[ITEM_SPRITE[item]].sprite, NULL);
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

static void animate_item_sprite(display_t *display, int anim, int item)
{
    sfSprite *sprite_item = display->tab[ITEM_SPRITE[item]].sprite;
    sfVector2f pos = sfSprite_getPosition(sprite_item);
    sfFloatRect sprites_bounds;

    if (pos.y > ITEM_CHEST_END_POS.y) {
        sfSprite_setScale(sprite_item, (sfVector2f){1 + anim * 0.02, 1 + anim * 0.02});
        sprites_bounds = sfSprite_getLocalBounds(sprite_item);
        pos.y = ITEM_CHEST_START_POS.y - ((anim - 3) * 5);
        pos.x = (1920 / 2) - ((100 * (1 + anim * 0.02)) / 2);
        sfSprite_setPosition(sprite_item, pos);
    }
}

static void change_animation(display_t *display, sfClock *clock, int *anim,
    int item)
{
    sfTime time = sfClock_getElapsedTime(clock);
    float seconds = time.microseconds / 1000000.0;
    sfSprite *sprite_chest = display->tab[CHEST_OPENING].sprite;
    
    sfVector2f pos;

    if (*anim < 4) {
        if (seconds > CHEST_ANIMATION_SPEED) {
            *anim += 1;
            sfClock_restart(clock);
        } else
            return;
    } else {
        if (seconds > ITEM_SPAWNING_SPEED) {
            *anim += 1;
            sfClock_restart(clock);
        } else
            return;
    }
    if (*anim < 4)
        sfSprite_setTextureRect(sprite_chest, get_rect(CHEST_OPENING, *anim));
    if (*anim > 3 && item != -1)
        animate_item_sprite(display, *anim, item);
}

void anim_chest_opening(display_t *display, sfText *text, int item)
{
    int keep = true;
    int animation = 0;
    sfClock *clock = sfClock_create();

    play_sound(display->sounds[CHEST_WAV]);
    usleep(500000);
    while (keep == 1 && sfRenderWindow_isOpen(display->window)) {
        change_animation(display, clock, &animation, item);
        display_chest(display, text, item);
        keep = manage_popup_events(display);
        if (item != -1 && animation >= 43)
            keep = false;
        if (item == -1 && animation >= 9)
            keep = false;
    }
    display_chest_obtained(display, text, item);
}
