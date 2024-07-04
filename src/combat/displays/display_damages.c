/*
** EPITECH PROJECT, 2024
** B-MUL-200-PAR-2-1-myrpg-pierre.pruvost
** File description:
** display_damages.c
*/

#include "combat.h"

#include <string.h>
#include <stdio.h>

static void set_position(sfText *hit, sfVector2f pos, int i)
{
    if (i < NB_ENTITY_SQUAD)
        sfText_setPosition(hit,
            (sfVector2f){pos.x + ALLY_HIT_INDI_X, HIT_INDICATOR_Y});
    else
        sfText_setPosition(hit,
            (sfVector2f){pos.x + MONSTER_HIT_INDI_X, HIT_INDICATOR_Y});
}

static void set_color_type(sfText *hit, cap_info_t *cap, int i)
{
    if (cap->type[i] == HEAL || cap->type[i] == HEAL_CRIT)
        sfText_setColor(hit, sfGreen);
    if (cap->type[i] == STAT_DOWN)
        sfText_setColor(hit, sfMagenta);
    if (cap->type[i] == STAT_UP)
        sfText_setColor(hit, sfYellow);
    if (cap->type[i] == BASIC || cap->type[i] == CRIT)
        sfText_setColor(hit, sfRed);
}

static void set_string(sfText *hit, cap_info_t *cap, int i)
{
    char *result = NULL;
    char hit_nb[100];

    sprintf(hit_nb, "%d", cap->entity_hit[i]);
    if (cap->type[i] == MISS) {
        sfText_setString(hit, "Miss");
        sfText_setColor(hit, sfBlue);
    } else {
        if (cap->type[i] == HEAL_CRIT || cap->type[i] == CRIT)
            result = strcat(hit_nb, "\nCrit");
        else
            result = strcat(hit_nb, " ");
        sfText_setString(hit, result);
    }
}

static void set_style(sfText *hit, sfFont *font)
{
    sfText_setFont(hit, font);
    sfText_setCharacterSize(hit, 30);
    sfText_setOutlineThickness(hit, 2);
    sfText_setOutlineColor(hit, sfBlack);
}

void display_damage_hit(display_t *display, combat_t *info,
    cap_info_t *cap)
{
    sfVector2f pos;
    sfText *hit = NULL;
    sfFont *font = sfFont_createFromFile(FONT);

    for (int i = 0; i < NB_ENTITY_SQUAD * 2; ++i) {
        if (info->field[i] != NULL && cap->entity_hit[i] != IGNORE) {
            pos = sfSprite_getPosition(info->field[i]->
                display[COMBAT_STATE]->sprite);
            hit = sfText_create();
            set_position(hit, pos, i);
            set_color_type(hit, cap, i);
            set_string(hit, cap, i);
            set_style(hit, font);
            sfRenderWindow_drawText(display->window, hit, NULL);
            sfText_destroy(hit);
        }
    }
    sfFont_destroy(font);
}
