/*
** EPITECH PROJECT, 2024
** B-MUL-200-PAR-2-1-myrpg-pierre.pruvost
** File description:
** display_xp_combat.c
*/

#include <stdio.h>
#include "combat.h"

static void set_position(sfText *hit, sfVector2f pos, int i)
{
    if (i < NB_ENTITY_SQUAD)
        sfText_setPosition(hit,
            (sfVector2f){pos.x + ALLY_HIT_INDI_X, HIT_INDICATOR_Y});
    else
        sfText_setPosition(hit,
            (sfVector2f){pos.x + MONSTER_HIT_INDI_X, HIT_INDICATOR_Y});
}

static void set_style(sfText *xp, sfFont *font)
{
    sfText_setFont(xp, font);
    sfText_setCharacterSize(xp, 30);
    sfText_setOutlineThickness(xp, 2);
    sfText_setColor(xp, sfWhite);
    sfText_setOutlineColor(xp, sfBlack);
}

void display_xp_combat(display_t *display, combat_t *info, int xp_gain,
    int i)
{
    sfText *xp = sfText_create();
    sfFont *font = sfFont_createFromFile(FONT);
    sfVector2f pos = {0, 0};
    char char_xp[100];

    sprintf(char_xp, "+%d xp", xp_gain);
    pos = sfSprite_getPosition(info->field[i]->
        display[COMBAT_STATE]->sprite);
    sfText_setString(xp, char_xp);
    set_position(xp, pos, i);
    set_style(xp, font);
    sfRenderWindow_drawText(display->window, xp, NULL);
    sfText_destroy(xp);
    sfFont_destroy(font);
}
