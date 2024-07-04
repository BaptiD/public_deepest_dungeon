/*
** EPITECH PROJECT, 2024
** event_menu_file.c
** File description:
** managing event
*/

#include <stdbool.h>
#include <stdio.h>

#include "my.h"
#include "game.h"
#include "entity.h"
#include "items.h"
#include "inventory.h"

static bool check_eq_items_member(entity_t *player, sfVector2i pos, int index)
{
    sfVector2f combined = {0};

    if (player->squad[index] == NULL)
        return false;
    for (int k = 0; k < NB_ITEMS_MEMBER; k++) {
        combined = combine_vectors(MEMBER_POS[index], MEMBER_ITEM_OFST[k]);
        if (is_in_zone(pos, combined, MEMBER_ITEM_SIZE) == true &&
            player->squad[index]->items[k] != EMPTY) {
            remove_stats(player, player->squad[index]->items[k], index);
            player->squad[index]->items[k] = EMPTY;
            return true;
        }
    }
    return false;
}

static bool manage_click_eq_items(entity_t *player, sfVector2i pos)
{
    int i = 0;

    for (int k = 0; k < NB_ENTITY_SQUAD; k++) {
        if (check_eq_items_member(player, pos, k) == true)
            return true;
    }
    return false;
}

static bool check_click_spell(entity_t *player, int *selection, sfVector2i pos,
    int index)
{
    if (is_in_zone(pos, SPELL_POS[index], SPELL_SIZE) == false)
        return false;
    if (selection[SPELL_SELECT] == index)
        selection[SPELL_SELECT] = OFF;
    else
        selection[SPELL_SELECT] = index;
    return true;
}

bool manage_click_spells(display_t *display, entity_t *player,
    int *selection, sfVector2i pos)
{
    if (selection[MEMBER_SELECT] == OFF)
        return true;
    if (is_in_hitbox(pos, REMOVE_MEMBER) == true) {
        if (selection[MEMBER_SELECT] != OFF &&
            player->squad[selection[MEMBER_SELECT]]->id != player->id &&
            confirmation(display, player, selection) == true) {
            destroy_entities(player->squad[selection[MEMBER_SELECT]]);
            player->squad[selection[MEMBER_SELECT]] = NULL;
            selection[MEMBER_SELECT] = OFF;
        }
        return true;
    }
    for (int k = 0; k < NB_SPELLS_MEMBER; k++) {
        if (check_click_spell(player, selection, pos, k) == true)
            return true;
    }
    return false;
}

static bool check_click_member(display_t *display, entity_t *player,
    int *selection, int index)
{
    sfVector2i pos = sfMouse_getPosition((sfWindow *)display->window);

    if (is_in_zone(pos, MEMBER_POS[index], MEMBER_SIZE) == false ||
        player->squad[index] == NULL)
        return false;
    if (drag_n_drop_member(display, player, selection, index) == 0)
        return true;
    if (selection[MEMBER_SELECT] == index)
        selection[MEMBER_SELECT] = OFF;
    else
        selection[MEMBER_SELECT] = index;    
    return true;
}

bool manage_click_members(display_t *display, entity_t *player,
    int *selection, sfVector2i pos)
{
    if (manage_click_eq_items(player, pos) == true)
        return true;
    for (int k = 0; k < NB_ENTITY_SQUAD; k++) {
        if (check_click_member(display, player, selection, k) == true)
            return true;
    }
    return false;
}

static bool check_click_item(display_t *display, entity_t *player,
    int *selection, int index)
{
    sfVector2i pos = sfMouse_getPosition((sfWindow *)display->window);

    if (is_in_zone(pos, ITEM_POS[index], ITEM_SIZE) == false ||
        player->inventory[index] == EMPTY)
        return false;
    if (drag_n_drop_item(display, player, selection,
        player->inventory[index]) == 0)
        return true;
    if (selection[ITEM_SELECT] == index)
        selection[ITEM_SELECT] = OFF;
    else
        selection[ITEM_SELECT] = index;
    return true;
}

bool manage_click_items(display_t *display, entity_t *player, int *selection,
    sfVector2i pos)
{
    if (is_in_hitbox(pos, REMOVE_ITEM) == true) {
        if (selection[ITEM_SELECT] != OFF &&
            confirmation(display, player, selection) == true) {
            remove_item(player, player->inventory[selection[ITEM_SELECT]]);
            player->inventory[selection[ITEM_SELECT]] = EMPTY;
            selection[ITEM_SELECT] = OFF;
        }
        return true;
    }
    for (int k = 0; k < INVENTORY_SIZE; k++) {
        if (check_click_item(display, player, selection, k) == true)
            return true;
    }
    return false;
}
