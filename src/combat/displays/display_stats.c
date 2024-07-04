/*
** EPITECH PROJECT, 2024
** B-MUL-200-PAR-2-1-myrpg-pierre.pruvost
** File description:
** display_stats.c
*/

#include <stdio.h>
#include "combat.h"

static void set_style(sfText *stats, sfFont *font)
{
    sfText_setFont(stats, font);
    sfText_setColor(stats, (sfColor){255, 255, 255, 255});
    sfText_setCharacterSize(stats, 25);
    sfText_setOutlineThickness(stats, 1);
    sfText_setOutlineColor(stats, sfBlack);
}

static void display_with_pos(display_t *display, sfText *stats,
    sfVector2f pos, char *str)
{
    sfText_setString(stats, str);
    sfText_setPosition(stats, pos);
    sfRenderWindow_drawText(display->window, stats, NULL);
}

static void display_stats(display_t *display, entity_t *entity,
    sfText *stats)
{
    int max_hp = entity->stats->hp;
    int act_hp = max_hp + entity->mod->hp;
    char str[256];

    sprintf(str, "Health : %i / %i", act_hp, max_hp);
    display_with_pos(display, stats, STATS_POS_COMBAT[0], str);
    sprintf(str, "Attack : %i", entity->stats->atk + entity->mod->atk);
    display_with_pos(display, stats, STATS_POS_COMBAT[1], str);
    sprintf(str, "Speed : %i", entity->stats->spd + entity->mod->spd);
    display_with_pos(display, stats, STATS_POS_COMBAT[2], str);
    sprintf(str, "Precision : %i", entity->stats->pre + entity->mod->pre);
    display_with_pos(display, stats, STATS_POS_COMBAT[3], str);
    sprintf(str, "Crit chance : %i", entity->stats->crt + entity->mod->crt);
    display_with_pos(display, stats, STATS_POS_COMBAT[4], str);
    sprintf(str, "Protection : %i", entity->stats->pro + entity->mod->pro);
    display_with_pos(display, stats, STATS_POS_COMBAT[5], str);
}

void display_stats_combat(display_t *display, combat_t *info)
{
    sfText *stats = sfText_create();
    sfFont *font = sfFont_createFromFile(FONT);

    set_style(stats, font);
    display_stats(display, info->field[info->turn], stats);
    sfFont_destroy(font);
    sfText_destroy(stats);
}
