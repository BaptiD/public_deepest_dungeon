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
#include "items.h"

static void display_drag(display_t *display, entity_t *player, int *selection,
    sfText *text)
{
    sfRenderWindow *window = display->window;
    sprite_t *sprites = display->tab;

    sfRenderWindow_clear(window, BG_DEFAULT_COLOR);
    display_inventory(display, player, text, selection);
    sfRenderWindow_drawSprite(window, sprites[ITEM_HINT].sprite, NULL);
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
    sfSprite_setPosition(display->tab[ITEM_HINT].sprite,
        (sfVector2f){pos.x, pos.y});
}

static int find_next_place(int *inv)
{
    for (int k = 0; k < NB_ITEMS_MEMBER; k += 1) {
        if (inv[k] == EMPTY)
            return k;
    }
    return OFF;
}

static void add_stats(entity_t *player, int id, int dest)
{
    player->squad[dest]->mod->hp -= ITEM_STATS[id].hp;
    player->squad[dest]->stats->hp += ITEM_STATS[id].hp;
    player->squad[dest]->stats->atk += ITEM_STATS[id].atk;
    player->squad[dest]->stats->spd += ITEM_STATS[id].spd;
    player->squad[dest]->stats->pre += ITEM_STATS[id].pre;
    player->squad[dest]->stats->pro += ITEM_STATS[id].pro;
    player->squad[dest]->stats->crt += ITEM_STATS[id].crt;
}

static int check_pos_action(entity_t *player, int id,
    sfVector2i pos)
{
    int dest = OFF;
    int next_place = OFF;

    for (int k = 0; k < NB_ENTITY_SQUAD; k++)
        if (is_in_zone(pos, MEMBER_POS[k], MEMBER_SIZE) == true)
            dest = k;
    if (dest == OFF || player->squad[dest] == NULL)
        return OFF;
    remove_item(player, id);
    next_place = find_next_place(player->squad[dest]->items);
    if (next_place == OFF)
        return 0;
    player->squad[dest]->items[next_place] = id;
    add_stats(player, id, dest);
    return 0;
}

static int unset_params(display_t *display, sfText *text, sfFont *font)
{
    sfText_destroy(text);
    sfFont_destroy(font);
    sfSprite_setScale(display->tab[ITEM_HINT].sprite, (sfVector2f){1, 1});
}

int drag_n_drop_item(display_t *display, entity_t *player, int *selection,
    int id)
{
    sfFont *font = sfFont_createFromFile(MENU_FONT);
    sfText *text = init_text(font, (sfVector2f){0, 0}, sfWhite, 25);
    sfVector2i pos = sfMouse_getPosition((sfWindow *)display->window);
    int hover = OFF;

    usleep(100000);
    sfSprite_setScale(display->tab[ITEM_HINT].sprite, (sfVector2f){2, 2});
    while (sfMouse_isButtonPressed(sfMouseLeft) &&
        sfRenderWindow_isOpen(display->window)) {
        pos = sfMouse_getPosition((sfWindow *)display->window);
        manage_events(display, pos, &hover);
        display_sugg(display, pos);
        display_drag(display, player, selection, text);
        sfRenderWindow_display(display->window);
    }
    unset_params(display, text, font);
    return check_pos_action(player, id, pos);
}
