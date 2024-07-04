/*
** EPITECH PROJECT, 2024
** event_menu_file.c
** File description:
** managing event
*/

#include "entity.h"
#include "game.h"
#include "sprites.h"
#include "inventory.h"

static void display_drag(display_t *display, entity_t *player, int *selection,
    sfText *text)
{
    sfRenderWindow *window = display->window;
    sprite_t *sprites = display->tab;

    sfRenderWindow_clear(window, BG_DEFAULT_COLOR);
    display_inventory(display, player, text, selection);
    sfRenderWindow_drawSprite(window, sprites[MEMBER_DRAG_HINT].sprite, NULL);
}

static char *manage_events(display_t *display, sfVector2i pos,
    int *hover)
{
    sfEvent event;

    while (sfRenderWindow_pollEvent(display->window, &event)) {
        if (event.type == sfEvtClosed)
            sfRenderWindow_close(display->window);
    }
}

static void display_sugg(display_t *display, sfVector2i pos)
{
    sfSprite_setPosition(display->tab[MEMBER_DRAG_HINT].sprite,
        (sfVector2f){pos.x, pos.y});
}

static int check_pos_action(entity_t *player, int index_click,
    sfVector2i pos, int *selection)
{
    int to_swap = OFF;

    for (int k = 0; k < NB_ENTITY_SQUAD; k++) {
        if (is_in_zone(pos, MEMBER_POS[k], MEMBER_SIZE) == true) {
            to_swap = k;
        }
    }
    if (to_swap == OFF || to_swap == index_click)
        return OFF;
    swap_entity(player, index_click, to_swap);
    if (selection[MEMBER_SELECT] == index_click)
        selection[MEMBER_SELECT] = to_swap;
    else if (selection[MEMBER_SELECT] == to_swap)
        selection[MEMBER_SELECT] = index_click;
    return 0;
}

int drag_n_drop_member(display_t *display, entity_t *player, int *selection,
    int index_click)
{
    sfFont *font = sfFont_createFromFile(MENU_FONT);
    sfText *text = init_text(font, (sfVector2f){0, 0}, sfWhite, 25);
    sfVector2i pos = sfMouse_getPosition((sfWindow *)display->window);
    int hover = -1;

    usleep(180000);
    while (sfMouse_isButtonPressed(sfMouseLeft) &&
        sfRenderWindow_isOpen(display->window)) {
        pos = sfMouse_getPosition((sfWindow *)display->window);
        manage_events(display, pos, &hover);
        display_sugg(display, pos);
        display_drag(display, player, selection, text);
        sfRenderWindow_display(display->window);
    }
    sfText_destroy(text);
    sfFont_destroy(font);
    return check_pos_action(player, index_click, pos, selection);
}
