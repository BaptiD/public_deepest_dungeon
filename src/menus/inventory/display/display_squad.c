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

static void display_name(display_t *display, entity_t *member, sfText *text,
    sfVector2f member_pos)
{
    sfFloatRect rect = {0};
    sfVector2f combined = combine_vectors(member_pos, MEMBER_NAME_OFST);

    if (member->name == NULL)
        return;
    sfText_setCharacterSize(text, NAME_SIZE);
    sfText_setString(text, member->name);
    rect = sfText_getLocalBounds(text);
    combined.x -= (rect.width / 2);
    sfText_setPosition(text, combined);
    sfRenderWindow_drawText(display->window, text, NULL);
}

static void display_hero(display_t *display, entity_t *member, sfText *text,
    sfVector2f member_pos)
{
    sfVector2f combined = combine_vectors(member_pos, MEMBER_PIC_OFST[member->id]);
    int index = SPRITES_INDEXES[member->id];
    sfSprite *to_display = display->tab[index].sprite;

    sfSprite_setScale(to_display, MEMBER_PIC_RATIO[member->id]);
    sfSprite_setOrigin(to_display, (sfVector2f){0, RESIZE[index].y});
    sfSprite_setPosition(to_display, combined);
    sfRenderWindow_drawSprite(display->window, to_display, NULL);
}

static void display_member_items(display_t *display, entity_t *member,
    sfVector2f member_pos, entity_t *player)
{
    sfVector2f combined = combine_vectors(member_pos, MEMBER_INV_OFST);
    sfVector2i pos = sfMouse_getPosition((sfWindow *)display->window);
    sfSprite *temp;

    sfSprite_setPosition(display->tab[SQUAD_ITEMS].sprite, combined);
    sfRenderWindow_drawSprite(display->window,
        display->tab[SQUAD_ITEMS].sprite, NULL);
    for (int k = 0; k < NB_ITEMS_MEMBER; k++) {
        if (member->items[k] != EMPTY) {
            check_eq_item(display, member_pos, pos, k);
            temp = display->tab[ITEM_SPRITE[member->items[k]]].sprite;
            combined = combine_vectors(member_pos, MEMBER_ITEM_OFST[k]);
            sfSprite_setPosition(temp, combined);
            sfSprite_setScale(temp, HALF_SIZE);
            sfRenderWindow_drawSprite(display->window, temp, NULL);
        }
    }
}

static void display_hp_bar(display_t *display, entity_t *member,
    sfVector2f member_pos)
{
    double act_hp = member->stats->hp + member->mod->hp;
    sfVector2f ratio = {(act_hp / member->stats->hp) / 1.2 * 1.08, 1 / 1.2};
    sfVector2f combined = combine_vectors(member_pos, MEMBER_HP_BAR_OFST);

    if (act_hp <= 0)
        ratio.x = 0;
    if (act_hp > member->stats->hp)
        ratio.x = 0.9;
    sfSprite_setRotation(display->tab[RED_BAR].sprite, 0);
    sfSprite_setRotation(display->tab[GREEN_BAR].sprite, 0);
    sfSprite_setPosition(display->tab[RED_BAR].sprite, combined);
    sfSprite_setPosition(display->tab[GREEN_BAR].sprite, combined);
    sfSprite_setScale(display->tab[GREEN_BAR].sprite, ratio);
    sfSprite_setScale(display->tab[RED_BAR].sprite,
        (sfVector2f){1.0 / 1.2 * 1.08, 1.0 / 1.2});
    sfRenderWindow_drawSprite(display->window,
        display->tab[RED_BAR].sprite, NULL);
    sfRenderWindow_drawSprite(display->window,
        display->tab[GREEN_BAR].sprite, NULL);
}

static void display_hp_txt(display_t *display, entity_t *member, sfText *text,
    sfVector2f member_pos)
{
    int max_hp = member->stats->hp;
    int act_hp = max_hp + member->mod->hp;
    sfVector2f pos = combine_vectors(member_pos, MEMBER_HP_TXT_OFST);
    char str[256];

    sfText_setCharacterSize(text, PREV_STATS_SIZE);
    sprintf(str, "HP : %i / %i", act_hp, max_hp);
    sfText_setString(text, str);
    sfText_setPosition(text, pos);
    sfRenderWindow_drawText(display->window, text, NULL);
}

static void display_xp_bar(display_t *display, entity_t *member,
    sfVector2f member_pos)
{
    double next_xp = (XP_TO_LVL_UP * pow(RATIO_XP_LVL_UP, member->level));
    sfVector2f ratio = {((double)member->xp / next_xp) / 1.2 * 1.08, 1 / 1.2};
    sfVector2f combined = combine_vectors(member_pos, MEMBER_XP_BAR_OFST);

    sfSprite_setRotation(display->tab[GREY_BAR].sprite, 0);
    sfSprite_setRotation(display->tab[BLUE_BAR].sprite, 0);
    sfSprite_setPosition(display->tab[GREY_BAR].sprite, combined);
    sfSprite_setPosition(display->tab[BLUE_BAR].sprite, combined);
    sfSprite_setScale(display->tab[BLUE_BAR].sprite, ratio);
    sfSprite_setScale(display->tab[GREY_BAR].sprite,
        (sfVector2f){1.0 / 1.2 * 1.08, 1.0 / 1.2});
    sfRenderWindow_drawSprite(display->window,
        display->tab[GREY_BAR].sprite, NULL);
    sfRenderWindow_drawSprite(display->window,
        display->tab[BLUE_BAR].sprite, NULL);
}

static void display_xp_txt(display_t *display, entity_t *member, sfText *text,
    sfVector2f member_pos)
{
    sfVector2f combined = combine_vectors(member_pos, MEMBER_XP_TXT_OFST);
    char str[256];

    if (member->level == 1)
        sprintf(str, "XP : %i / %i", member->xp,
            (int)(XP_TO_LVL_UP * RATIO_XP_LVL_UP));
    else
        sprintf(str, "XP : %i / %i", member->xp,
            (XP_TO_LVL_UP * (int)pow(RATIO_XP_LVL_UP, member->level + 1)));
    sfText_setString(text, str);
    sfText_setPosition(text, combined);
    sfRenderWindow_drawText(display->window, text, NULL);
}

static void display_level(display_t *display, entity_t *member, sfText *text,
    sfVector2f member_pos)
{
    sfVector2f combined = combine_vectors(member_pos, MEMBER_LEVEL_OFST);
    sfFloatRect rect;
    char str[256];

    sfText_setCharacterSize(text, STAT_LVL_SIZE);
    sprintf(str, "LEVEL %i", member->level);
    sfText_setString(text, str);
    rect = sfText_getLocalBounds(text);
    combined.x -= (rect.width / 2);
    sfText_setPosition(text, combined);
    sfRenderWindow_drawText(display->window, text, NULL);
}

static void display_member(display_t *display, entity_t *player,
    sfText *text, int k)
{
    entity_t *member = player->squad[k];
    sfVector2f member_pos = MEMBER_POS[k];

    display_hero(display, member, text, member_pos);
    display_name(display, member, text, member_pos);
    display_member_items(display, member, member_pos, player);
    display_hp_bar(display, member, member_pos);
    display_hp_txt(display, member, text, member_pos);
    display_xp_bar(display, member, member_pos);
    display_xp_txt(display, member, text, member_pos);
    display_level(display, member, text, member_pos);
}

void display_squad(display_t *display, entity_t *player, sfText *text,
    int *selection)
{
    for (int k = 0; k < NB_ENTITY_SQUAD; k++) {
        if (player->squad[k] != NULL)
            display_member(display, player, text, k);
    }
}
