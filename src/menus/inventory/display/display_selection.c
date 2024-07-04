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
#include "capacity.h"
#include "inventory.h"

static void display_item_select(display_t *display, entity_t *player,
    sfText *text, int selection)
{
    int id = player->inventory[selection];
    char str[256];
    
    sfText_setString(text, ITEM_NAME[id]);
    sfText_setCharacterSize(text, ITEM_NAME_SIZE);
    sfText_setPosition(text, ITEM_NAME_POS);
    sfRenderWindow_drawText(display->window, text, NULL);
    sfText_setString(text, ITEM_DESCRIPTION[id]);
    sfText_setCharacterSize(text, ITEM_DESCRIPTION_SIZE);
    sfText_setPosition(text, ITEM_DESCRIPTION_POS);
    sfRenderWindow_drawText(display->window, text, NULL);
    display_part_stats(display, text, ITEM_STATS[id],
        STATS_POS[ITEM_STATS_POS]);
}

static void display_member_select(display_t *display, entity_t *player,
    sfText *text, int selection)
{
    sfText_setCharacterSize(text, INFO_TITLE);
    sfText_setPosition(text, MEMBER_STATS_TITLE);
    sfText_setString(text, "Stats");
    sfRenderWindow_drawText(display->window, text, NULL);
    sfText_setPosition(text, MEMBER_SPELL_TITLE);
    sfText_setString(text, "Spells");
    sfRenderWindow_drawText(display->window, text, NULL);
    display_member_stats(display, text, *(player->squad[selection]->stats),
        player->squad[selection]->items);
}

static void display_range(display_t *display, int *range)
{
    sfVector2f pos = SPELL_RANGE;

    for (int k = 0; k < NB_POS; k++) {
        if (range[k] == 1) {
            sfSprite_setPosition(display->tab[CAN_RANGE].sprite, pos);
            sfRenderWindow_drawSprite(display->window,
                display->tab[CAN_RANGE].sprite, NULL);
        } else {
            sfSprite_setPosition(display->tab[CANT_RANGE].sprite, pos);
            sfRenderWindow_drawSprite(display->window,
                display->tab[CANT_RANGE].sprite, NULL);
        }
        pos.x += 52;
    }
}

static void display_focus(display_t *display, int *focus)
{
    sfVector2f pos = SPELL_FOCUS;

    for (int k = 0; k < NB_POS; k++) {
        if (focus[k + NB_POS] == 1) {
            sfSprite_setPosition(display->tab[CAN_FOCUS].sprite, pos);
            sfRenderWindow_drawSprite(display->window,
                display->tab[CAN_FOCUS].sprite, NULL);
        } else {
            sfSprite_setPosition(display->tab[CANT_FOCUS].sprite, pos);
            sfRenderWindow_drawSprite(display->window,
                display->tab[CANT_FOCUS].sprite, NULL);
        }
        pos.x += 52;
    }
}

static void display_spell_select(display_t *display, entity_t *player,
    sfText *text, int *selection)
{
    int member_id = selection[MEMBER_SELECT];
    int spell_id = selection[SPELL_SELECT];
    int spell_index = player->squad[member_id]->capacities[spell_id];
    capa_t spell = CAPACITY[spell_index];
    sfVector2f old_scale = sfSprite_getScale(display->tab[CAN_FOCUS].sprite);

    for (int k = CAN_FOCUS; k <= CANT_RANGE; k++)
        sfSprite_setScale(display->tab[k].sprite, FULL_SIZE);
    sfText_setCharacterSize(text, ITEM_NAME_SIZE);
    sfText_setPosition(text, SPELL_NAME);
    sfText_setString(text, CAPACITY[spell_index].name);
    sfRenderWindow_drawText(display->window, text, NULL);
    display_range(display, spell.range);
    display_focus(display, spell.focus);
    for (int k = CAN_FOCUS; k <= CANT_RANGE; k++)
        sfSprite_setScale(display->tab[k].sprite, old_scale);
}

void display_selection(display_t *display, entity_t *player, sfText *text,
    int *selection)
{
    if (selection[ITEM_SELECT] != OFF)
        display_item_select(display, player, text, selection[ITEM_SELECT]);
    if (selection[MEMBER_SELECT] != OFF)
        display_member_select(display, player, text, selection[MEMBER_SELECT]);
    if (selection[SPELL_SELECT] != OFF && selection[MEMBER_SELECT] != OFF)
        display_spell_select(display, player, text, selection);
}
