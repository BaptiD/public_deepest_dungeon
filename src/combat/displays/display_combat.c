/*
** EPITECH PROJECT, 2024
** B-MUL-200-PAR-2-1-myrpg-pierre.pruvost
** File description:
** display_combat.c
*/

#include <stdio.h>
#include "combat.h"
#include "capacity.h"
#include "my.h"

void draw_turn_entity(display_t *display, combat_t *info)
{
    sfVector2f pos = sfSprite_getPosition(info->field[info->turn]->
        display[COMBAT_STATE]->sprite);

    if (info->turn < NB_ENTITY_SQUAD) {
        sfSprite_setPosition(display->tab[TURN_CHOOSE].sprite, (sfVector2f)
            {pos.x + ALLY_TURN_INDICATOR_X, TURN_INDICATOR_Y});
        sfRenderWindow_drawSprite(display->window,
            display->tab[TURN_CHOOSE].sprite, NULL);
    } else {
        sfSprite_setPosition(display->tab[TURN_CHOOSE].sprite, (sfVector2f)
            {pos.x + MONSTER_TURN_INDICATOR_X, TURN_INDICATOR_Y});
        sfRenderWindow_drawSprite(display->window,
            display->tab[TURN_CHOOSE].sprite, NULL);
    }
}

static void display_focus_pos(display_t *display, int i, combat_t *info)
{
    sfVector2f pos = sfSprite_getPosition(info->field[i]->
        display[COMBAT_STATE]->sprite);

    if (i < NB_ENTITY_SQUAD) {
        sfSprite_setPosition(display->tab[SELECT_BUFF].sprite,
            (sfVector2f){pos.x + ALLY_FOCUS_INDI_X, FOCUS_INDICATOR_Y});
        sfRenderWindow_drawSprite(display->window,
            display->tab[SELECT_BUFF].sprite, NULL);
    } else {
        sfSprite_setPosition(display->tab[SELECT_DMG].sprite,
            (sfVector2f){pos.x + MONSTER_FOCUS_INDI_X, FOCUS_INDICATOR_Y});
        sfRenderWindow_drawSprite(display->window,
            display->tab[SELECT_DMG].sprite, NULL);
    }
}

static void draw_focus(display_t *display, combat_t *info)
{
    if (info->capa_pressed == 0)
        return;
    if (CAPACITY[info->field[info->turn]->capacities
        [info->capa_pressed - 3]].type == SELF) {
        display_focus_pos(display, info->turn, info);
        return;
    }
    for (int i = 0; i < NB_ENTITY_SQUAD * 2; ++i) {
        if (info->field[i] != NULL && CAPACITY[info->field[info->turn]->
            capacities[info->capa_pressed - 3]].focus[i] == 1 &&
            info->field[i]->status != DEAD) {
            display_focus_pos(display, i, info);
        }
    }
}

static void draw_description_capacity(display_t *display, combat_t *info)
{
    sfText *text = NULL;
    sfFont *font = NULL;
    sfVector2f pos = POS_DESCRIPTION_COMBAT;

    if (info->capa_pressed == 0)
        return;
    text = sfText_create();
    font = sfFont_createFromFile(MENU_FONT);
    sfText_setFont(text, font);
    sfText_setPosition(text, pos);
    sfText_setString(text, CAPACITY[info->field[info->turn]->
        capacities[info->capa_pressed - 3]].name);
    sfRenderWindow_drawText(display->window, text, NULL);
    pos.y += 50;
    sfText_setCharacterSize(text, 20);
    sfText_setPosition(text, pos);
    sfText_setString(text, CAPACITY[info->field[info->turn]->
        capacities[info->capa_pressed - 3]].description);
    sfRenderWindow_drawText(display->window, text, NULL);
    sfText_destroy(text);
    sfFont_destroy(font);
}

void draw_filed_entity(sfRenderWindow *window, combat_t *info)
{
    for (int i = 0; i < NB_ENTITY_SQUAD; ++i)
        if (info->field[i] != NULL) {
            sfRenderWindow_drawSprite(window, info->field[i]->
                display[COMBAT_STATE]->sprite, NULL);
        }
    for (int i = 4; i < NB_ENTITY_SQUAD * 2; ++i)
        if (info->field[i] != NULL) {
            sfRenderWindow_drawSprite(window, info->field[i]->
                display[COMBAT_STATE]->sprite, NULL);
        }
}

static void draw_position_hud(display_t *display)
{
    sfText *text = sfText_create();
    sfFont *font = sfFont_createFromFile(FONT);
    sfVector2f pos = {0, 0};
    char index[3];

    sfText_setFont(text, font);
    sfText_setCharacterSize(text, 20);
    sfText_setColor(text, (sfColor){130, 130, 130, 255});
    for (int i = 0; i < NB_ENTITY_SQUAD * 2; ++i) {
        sprintf(index, "%d", i + 1);
        sfText_setString(text, index);
        pos = (sfVector2f){(i * ENTITY_DISTANCE) +
            96, ENTITY_POS_Y + COMBAT_SPRITE_SIZE + 20};
        if (i >= NB_ENTITY_SQUAD)
            pos.x += COMBAT_SPRITE_SIZE;
        sfText_setPosition(text, pos);
        sfRenderWindow_drawText(display->window, text, NULL);
    }
    sfText_destroy(text);
    sfFont_destroy(font);
}

void draw_combat(display_t *display, combat_t *info)
{
    sfRenderWindow_clear(display->window, sfBlack);
    sfRenderWindow_drawSprite(display->window,
        info->background.sprite, NULL);
    if (info->turn < NB_ENTITY_SQUAD) {
        display_stats_combat(display, info);
        display_capacities_combat(display, info);
    }
    display_health_bar(display->window, display->tab, info);
    display_lvl_combat(display, info);
    draw_position_hud(display);
    draw_filed_entity(display->window, info);
    draw_turn_entity(display, info);
    draw_focus(display, info);
    draw_description_capacity(display, info);
}
