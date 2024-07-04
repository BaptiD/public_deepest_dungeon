/*
** EPITECH PROJECT, 2024
** event_menu_file.c
** File description:
** managing event
*/

#include <stdbool.h>
#include <stdio.h>
#include <math.h>

#include "game.h"
#include "entity.h"
#include "inventory.h"

void check_eq_item(display_t *display, sfVector2f member_pos, sfVector2i pos,
    int index)
{
    sfVector2f combined = combine_vectors(member_pos, MEMBER_ITEM_OFST[index]);

    if (is_in_zone(pos, combined, MEMBER_ITEM_SIZE) == true) {
        sfSprite_setPosition(display->tab[EQ_ITEM_HOVER].sprite, combined);
        sfRenderWindow_drawSprite(display->window,
            display->tab[EQ_ITEM_HOVER].sprite, NULL);
    }
}

static bool in_member_inv(sfVector2i pos, int nb)
{
    sfVector2f combined = combine_vectors(MEMBER_POS[nb], MEMBER_INV_OFST);

    if (is_in_zone(pos, combined, MEMBER_INV_SIZE) == true)
        return true;
    return false;
}

static void check_in_members(display_t *display, entity_t *player,
    sfVector2i pos, int *selection)
{
    for (int k = 0; k < NB_ENTITY_SQUAD; k++) {
        if (is_in_zone(pos, MEMBER_POS[k], MEMBER_SIZE) == true &&
            in_member_inv(pos, k) == false) {
            sfSprite_setTextureRect(display->tab[INVENTORY_MEMBER].sprite,
                get_rect(INVENTORY_MEMBER, 0));
            sfSprite_setPosition(display->tab[INVENTORY_MEMBER].sprite,
                MEMBER_POS[k]);
            sfRenderWindow_drawSprite(display->window,
                display->tab[INVENTORY_MEMBER].sprite, NULL);
        }
        if (selection[MEMBER_SELECT] == k) {
            sfSprite_setPosition(display->tab[INVENTORY_MEMBER].sprite,
                MEMBER_POS[k]);
            sfSprite_setTextureRect(display->tab[INVENTORY_MEMBER].sprite,
                get_rect(INVENTORY_MEMBER, 1));
            sfRenderWindow_drawSprite(display->window,
                display->tab[INVENTORY_MEMBER].sprite, NULL);
        }
    }
}

static void check_in_items(display_t *display, entity_t *player,
    sfVector2i pos, int *selection)
{
    for (int k = 0; k < INVENTORY_SIZE; k++) {
        if (is_in_zone(pos, ITEM_POS[k], ITEM_SIZE) == true) {
            sfSprite_setTextureRect(display->tab[INVENTORY_ITEM].sprite,
                get_rect(INVENTORY_ITEM, 0));
            sfSprite_setPosition(display->tab[INVENTORY_ITEM].sprite,
                ITEM_POS[k]);
            sfRenderWindow_drawSprite(display->window,
                display->tab[INVENTORY_ITEM].sprite, NULL);
        }
        if (selection[ITEM_SELECT] == k) {
            sfSprite_setPosition(display->tab[INVENTORY_ITEM].sprite,
                ITEM_POS[k]);
            sfSprite_setTextureRect(display->tab[INVENTORY_ITEM].sprite,
                get_rect(INVENTORY_ITEM, 1));
            sfRenderWindow_drawSprite(display->window,
                display->tab[INVENTORY_ITEM].sprite, NULL);
        }
    }
}

static void check_in_spells(display_t *display, entity_t *player,
    sfVector2i pos, int *selection)
{
    if (selection[MEMBER_SELECT] == OFF)
        return;
    for (int k = 0; k < NB_SPELLS_MEMBER; k++) {
        if (is_in_zone(pos, SPELL_POS[k], SPELL_SIZE) == true) {
            sfSprite_setTextureRect(display->tab[SPELL_A + k].sprite,
                get_rect(SPELL_A, 1));
        } else {
            sfSprite_setTextureRect(display->tab[SPELL_A + k].sprite,
                get_rect(SPELL_A, 0));
        }
        sfRenderWindow_drawSprite(display->window,
                display->tab[SPELL_A + k].sprite, NULL);
        if (selection[SPELL_SELECT] == k) {
            sfSprite_setTextureRect(display->tab[SPELL_A + k].sprite,
                get_rect(SPELL_A, 2));
            sfRenderWindow_drawSprite(display->window,
                display->tab[SPELL_A + k].sprite, NULL);
        }
    }
}

static void display_remove_item(display_t *display, entity_t *player,
    sfVector2i pos, int *selection)
{
    if (selection[ITEM_SELECT] != OFF) {
        if (is_in_hitbox(pos, REMOVE_ITEM) == true) {
            sfSprite_setTextureRect(display->tab[REMOVE_ITEM].sprite,
                get_rect(REMOVE_ITEM, 1));
        } else {
            sfSprite_setTextureRect(display->tab[REMOVE_ITEM].sprite,
                get_rect(REMOVE_ITEM, 0));
        }
        sfRenderWindow_drawSprite(display->window,
            display->tab[REMOVE_ITEM].sprite, NULL);
    }
}

static void display_remove_member(display_t *display, entity_t *player,
    sfVector2i pos, int *selection)
{
    if (selection[MEMBER_SELECT] != OFF &&
        player->squad[selection[MEMBER_SELECT]]->id != player->id) {
        if (is_in_hitbox(pos, REMOVE_MEMBER) == true) {
            sfSprite_setTextureRect(display->tab[REMOVE_MEMBER].sprite,
                get_rect(REMOVE_MEMBER, 1));
        } else {
            sfSprite_setTextureRect(display->tab[REMOVE_MEMBER].sprite,
                get_rect(REMOVE_MEMBER, 0));
        }
        sfRenderWindow_drawSprite(display->window,
            display->tab[REMOVE_MEMBER].sprite, NULL);
    }
}

void display_buttons(display_t *display, entity_t *player, int *selection)
{
    sfVector2i pos = sfMouse_getPosition((sfWindow *)display->window);

    check_in_members(display, player, pos, selection);
    check_in_spells(display, player, pos, selection);
    check_in_items(display, player, pos, selection);
    display_remove_item(display, player, pos, selection);
    display_remove_member(display, player, pos, selection);
}
