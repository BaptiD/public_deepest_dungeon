/*
** EPITECH PROJECT, 2024
** event_menu_file.c
** File description:
** managing event
*/

#include <stdbool.h>

#include "tuto.h"
#include "menus.h"
#include "game.h"
#include "entity.h"
#include "my.h"

static void display_menu(sfRenderWindow *window, sprite_t *sprites)
{
    sfRenderWindow_clear(window, BG_DEFAULT_COLOR);
    sfRenderWindow_drawSprite(window, sprites[LOBBY_BCKG].sprite, NULL);
    sfRenderWindow_drawSprite(window, sprites[START_GAME].sprite, NULL);
    sfRenderWindow_drawSprite(window, sprites[QUIT_GAME].sprite, NULL);
    sfRenderWindow_drawSprite(window, sprites[LOAD_SAVE].sprite, NULL);
    sfRenderWindow_drawSprite(window, sprites[OPTIONS].sprite, NULL);
    sfRenderWindow_drawSprite(window, sprites[HELP].sprite, NULL);
    sfRenderWindow_display(window);
}

sfIntRect get_rect_menu(int index, int offset)
{
    sfIntRect rect;

    rect.left = MENU_IMG_RESIZE[index].x * offset;
    rect.top = 0;
    rect.width = MENU_IMG_RESIZE[index].x;
    rect.height = MENU_IMG_RESIZE[index].y;
    return rect;
}

int is_in_hitbox_menu(sfVector2i pos, int index)
{
    int resx = pos.x - MENU_IMG_POSITION[index].x;
    int resy = pos.y - MENU_IMG_POSITION[index].y;

    if (resx < MENU_IMG_RESIZE[index].x && resx > 0)
        if (resy < MENU_IMG_RESIZE[index].y && resy > 0)
            return true;
    return false;
}

static int launch_game(display_t *display, sprite_t *sprites)
{
    int hero = 0;
    entity_t *player = NULL;
    dungeon_t *dungeon = NULL;

    play_sound(display->sounds[START_WAV]);
    if (tuto_loop(display) == false)
        return true;
    hero = hero_selection(display, sprites);
    play_sound(display->sounds[START_WAV]);
    if (hero == -1)
        return false;
    player = setting_entity_from_file(hero);
    dungeon = setup_dungeon(player);
    logs(SUCCESS, "Game entities launched");
    game(display, player, dungeon);
    destroy_entities(player);
    return true;
}

static int manage_menu_click(display_t *display, sprite_t *sprites)
{
    sfVector2i pos = sfMouse_getPosition((sfWindow *)display->window);

    if (is_in_hitbox_menu(pos, QUIT_GAME) == true) {
        play_sound(display->sounds[CLICK_WAV]);
        usleep(100000);
        return false;
    }
    if (is_in_hitbox_menu(pos, START_GAME) == true)
        return launch_game(display, sprites);
    if (is_in_hitbox_menu(pos, LOAD_SAVE) == true) {
        play_sound(display->sounds[CLICK_WAV]);
        return set_save_from_file(display);
    }
    if (is_in_hitbox_menu(pos, OPTIONS) == true) {
        options(display, sprites);
        return true;
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

    if (manage_button_hover(display, sprites, START_GAME, hover) == IN)
        buttons = IN;
    if (manage_button_hover(display, sprites, QUIT_GAME, hover) == IN)
        buttons = IN;
    if (manage_button_hover(display, sprites, LOAD_SAVE, hover) == IN)
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
    int *hover)
{
    sfEvent event;
    int menu = true;

    while (sfRenderWindow_pollEvent(display->window, &event)) {
        manage_options_hover(display, sprites, hover);
        if (event.type == sfEvtClosed)
            sfRenderWindow_close(display->window);
        if (event.type == sfEvtMouseButtonPressed)
            menu = manage_menu_click(display, sprites);
        if (menu == false)
            return menu;
    }
    return menu;
}

int lobby_loop(display_t *display)
{
    int menu = true;
    sprite_t *sprites = init_menu_sprites();
    int hover = OUT;

    while (sfRenderWindow_isOpen(display->window) && menu == true) {
        display_menu(display->window, sprites);
        menu = manage_menu_events(display, sprites, &hover);
    }
    destroy_sprites(sprites, NB_MENU_IMG);
    return 0;
}
