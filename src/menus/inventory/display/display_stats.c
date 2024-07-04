/*
** EPITECH PROJECT, 2024
** event_menu_file.c
** File description:
** managing event
*/

#include <stdbool.h>
#include <stdio.h>
#include <math.h>

#include "my.h"
#include "game.h"
#include "entity.h"
#include "items.h"
#include "inventory.h"

static int *get_item_stats(int *items, int *stats)
{
    for (int k = 0; k < NB_ITEMS_MEMBER; k++) {
        if (items[k] != EMPTY) {
            stats[0] += ITEM_STATS[items[k]].hp;
            stats[1] += ITEM_STATS[items[k]].atk;
            stats[2] += ITEM_STATS[items[k]].crt;
            stats[3] += ITEM_STATS[items[k]].pre;
            stats[4] += ITEM_STATS[items[k]].pro;
            stats[5] += ITEM_STATS[items[k]].spd;
        }
    }
    return stats;
}

static void display_stat(display_t *display, sfText *text, int member_stat,
    int items_stat)
{
    sfVector2f pos = sfText_getPosition(text);
    int text_size = 0;
    char str[256];

    sprintf(str, "%d", member_stat);
    sfText_setString(text, str);
    text_size = (int)sfText_getLocalBounds(text).width;
    pos.x += text_size + 10;
    if (items_stat > 0) {
        sfText_setColor(text, sfGreen);
        sfSprite_setPosition(display->tab[STAT_UP_ARROW].sprite, pos);
        sfRenderWindow_drawSprite(display->window, display->tab[STAT_UP_ARROW].sprite, NULL);
    }
    else if (items_stat < 0) {
        sfText_setColor(text, sfRed);
        sfSprite_setPosition(display->tab[STAT_DOWN_ARROW].sprite, pos);
        sfRenderWindow_drawSprite(display->window, display->tab[STAT_DOWN_ARROW].sprite, NULL);
    }
}

static void display_stat_sprite(display_t *display, sfVector2f combined, int index)
{
    combined.x -= 45;
    sfSprite_setPosition(display->tab[index].sprite, combined);
    sfRenderWindow_drawSprite(display->window,
        display->tab[index].sprite, NULL);
}

void display_member_stats(display_t *display, sfText *text, stats_t stats,
    int *items)
{
    int cast_stats[6] = {stats.hp, stats.atk, stats.crt, stats.pre,
        stats.pro, stats.spd};
    int items_stat[6] = {0};
    sfVector2f pos = STATS_POS[MEMBER_STATS_POS];
    sfVector2f combined = {0};

    get_item_stats(items, items_stat);
    sfText_setCharacterSize(text, STATS_SIZE);
    for (int k = 0; k < NB_STATS; k++) {
        combined = combine_vectors(pos, STAT_OFST[k]);
        sfText_setPosition(text, combined);
        display_stat(display, text, cast_stats[k], items_stat[k]);
        display_stat_sprite(display, combined, STAT_SPR_INDEX[k]);
        sfRenderWindow_drawText(display->window, text, NULL);
        sfText_setColor(text, sfWhite);
    }
}
