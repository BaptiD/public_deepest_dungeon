/*
** EPITECH PROJECT, 2024
** pnj
** File description:
** functions to manage_pnj
*/

#include <stdio.h>
#include <stdbool.h>

#include "items.h"
#include "game.h"
#include "combat.h"
#include "my.h"

sfBool next_to_chest(dungeon_t *dungeon, entity_t *player, int x, int y)
{
    if (player->pos[1] + y >= 0 && player->pos[1] + y <= 19 &&
        player->pos[0] + x >= 0 && player->pos[0] + x <= 19) {
        if (ACTUAL_MAP.char_map[player->pos[1] + y][player->pos[0] + x]
            == MAP_CHEST) {
            ACTUAL_MAP.char_map[player->pos[1] + y][player->pos[0] + x] = ' ';
            return true;
        }
    }
    return false;
}

sfBool is_close_to_chest(dungeon_t *dungeon, entity_t *player)
{
    if (next_to_chest(dungeon, player, -1, -1) == true)
        return true;
    if (next_to_chest(dungeon, player, -1, 0) == true)
        return true;
    if (next_to_chest(dungeon, player, -1, 1) == true)
        return true;
    if (next_to_chest(dungeon, player, 0, -1) == true)
        return true;
    if (next_to_chest(dungeon, player, 0, 1) == true)
        return true;
    if (next_to_chest(dungeon, player, 1, -1) == true)
        return true;
    if (next_to_chest(dungeon, player, 1, 0) == true)
        return true;
    if (next_to_chest(dungeon, player, 1, 1) == true)
        return true;
    return false;
}

static bool is_in_inventory(int *inventory, int item)
{
    for (int i = 0; i < INVENTORY_SIZE; i++) {
        if (inventory[i] == item)
            return true;
    }
    return false;
}

int chest_offer(int *inventory)
{
    int item = get_random_nb(0, NB_ITEMS - 1);

    while (is_in_inventory(inventory, item) == true)
        item = get_random_nb(0, NB_ITEMS - 1);
    return item;
}

void get_an_item(display_t *display, entity_t *player, int chance)
{
    int i = 0;
    int item = -1;

    for (; player->inventory[i] != -1 && i < INVENTORY_SIZE; i++);
    if (i == INVENTORY_SIZE)
        return;
    if (get_random_nb(1, 100) < chance)
        item = chest_offer(player->inventory);
    if (chance == ITEM_CHEST_CHANCE)
        chest_opening(display, item);
    player->inventory[i] = item;
}

void manage_chest(dungeon_t *dungeon, entity_t *player, display_t *display)
{
    if (sfKeyboard_isKeyPressed(sfKeyE) == true) {
        if (is_close_to_chest(dungeon, player) == true) {
            get_an_item(display, player, ITEM_CHEST_CHANCE);
            get_sprite_map(dungeon, player);
        }
    }
}
