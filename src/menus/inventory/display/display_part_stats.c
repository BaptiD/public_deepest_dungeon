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

static void display_stat_text(display_t *display, sfText *text, int stat,
    sfVector2f combined)
{
    char str[256];

    if (stat > 0) {
        sprintf(str, "+%d", stat);
        sfText_setColor(text, sfGreen);
    }
    else {
        sprintf(str, "%d", stat);
        sfText_setColor(text, sfRed);
    }
    sfText_setCharacterSize(text, STATS_SIZE);
    sfText_setPosition(text, combined);
    sfText_setString(text, str);
    sfRenderWindow_drawText(display->window, text, NULL);
    sfText_setColor(text, sfWhite);
}

void display_part_stats(display_t *display, sfText *text, stats_t stats,
    sfVector2f pos)
{
    int cast_stats[6] = {stats.hp, stats.atk, stats.crt, stats.pre,
        stats.pro, stats.spd};
    sfVector2f combined = {0};
    sfSprite *sprite;
    int next = 0;

    for (int k = 0; k < NB_STATS; k++) {
        if (cast_stats[k] != 0) {
            combined = combine_vectors(pos, STAT_OFST[next]);
            display_stat_text(display, text, cast_stats[k], combined);
            combined.x -= 40;
            sprite = display->tab[STAT_SPR_INDEX[k]].sprite;
            sfSprite_setPosition(sprite, combined);
            sfRenderWindow_drawSprite(display->window, sprite, NULL);
            next += 1;
        }
    }
}
