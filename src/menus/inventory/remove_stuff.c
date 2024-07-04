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

void remove_stats(entity_t *player, int id, int dest)
{
    player->squad[dest]->mod->hp += ITEM_STATS[id].hp;
    player->squad[dest]->stats->hp -= ITEM_STATS[id].hp;
    player->squad[dest]->stats->atk -= ITEM_STATS[id].atk;
    player->squad[dest]->stats->spd -= ITEM_STATS[id].spd;
    player->squad[dest]->stats->pre -= ITEM_STATS[id].pre;
    player->squad[dest]->stats->pro -= ITEM_STATS[id].pro;
    player->squad[dest]->stats->crt -= ITEM_STATS[id].crt;
}

static void seek_for_item(entity_t *player, int item, int member)
{
    for (int k = 0; k < NB_ITEMS_MEMBER; k++) {
        if (item == player->squad[member]->items[k]) {
            player->squad[member]->items[k] = EMPTY;
            remove_stats(player, item, member);
        }
    }
}

void remove_item(entity_t *player, int item)
{
    for (int k = 0; k < NB_ENTITY_SQUAD; k++) {
        if (player->squad[k] != NULL) {
            seek_for_item(player, item, k);
        }
    }
}
