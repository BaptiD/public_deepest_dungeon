/*
** EPITECH PROJECT, 2024
** B-MUL-200-PAR-2-1-myrpg-pierre.pruvost
** File description:
** display_hp_bar.c
*/

#include "combat.h"
#include <stdio.h>

static void change_hp_pos(combat_t *info, sprite_t *sprites, int i)
{
    sfVector2f pos = sfSprite_getPosition(info->field[i]->
        display[COMBAT_STATE]->sprite);
    sfVector2f monster = (sfVector2f){pos.x + HP_BAR_MONSTER_X, HP_BAR_POS_Y};
    sfVector2f ally = (sfVector2f){pos.x + HP_BAR_ALLY_X, HP_BAR_POS_Y};

    if (i < NB_ENTITY_SQUAD) {
        sfSprite_setPosition(sprites[HP_BAR_1].sprite, ally);
        ally.x += 9;
        ally.y += RESIZE[HP_BAR_1].y - 5;
        sfSprite_setPosition(sprites[RED_BAR].sprite, ally);
        sfSprite_setPosition(sprites[GREEN_BAR].sprite, ally);
    } else {
        sfSprite_setPosition(sprites[HP_BAR_1].sprite, monster);
        monster.x += 5;
        monster.y += RESIZE[HP_BAR_1].y - 5;
        sfSprite_setPosition(sprites[RED_BAR].sprite, monster);
        sfSprite_setPosition(sprites[GREEN_BAR].sprite, monster);
    }
}

static void change_lvl_pos(combat_t *info, sfText *lvl, int i)
{
    sfVector2f pos = sfSprite_getPosition(info->field[i]->
        display[COMBAT_STATE]->sprite);
    sfVector2f monster = (sfVector2f){pos.x + LVL_MONSTER_X, LVL_POS_Y};
    sfVector2f ally = (sfVector2f){pos.x + LVL_ALLY_X, LVL_POS_Y};

    if (i < NB_ENTITY_SQUAD) {
        sfText_setPosition(lvl, ally);
    } else {
        sfText_setPosition(lvl, monster);
    }
}

void display_lvl_combat(display_t *display, combat_t *info)
{
    sfText *lvl = NULL;
    sfFont *font = sfFont_createFromFile(FONT);
    char str_lvl[100];

    for (int i = 0; i < NB_ENTITY_SQUAD * 2; ++i) {
        if (info->field[i] != NULL) {
            lvl = sfText_create();
            sprintf(str_lvl, "%d", info->field[i]->level);
            sfText_setString(lvl, str_lvl);
            change_lvl_pos(info, lvl, i);
            sfText_setFont(lvl, font);
            sfText_setCharacterSize(lvl, 25);
            sfText_setOutlineThickness(lvl, 2);
            sfText_setOutlineColor(lvl, sfBlack);
            sfRenderWindow_drawText(display->window, lvl, NULL);
            sfText_destroy(lvl);
        }
    }
    sfFont_destroy(font);
}

static int get_actual_hp(entity_t *entity)
{
    int act_hp = entity->stats->hp + entity->mod->hp;

    if (act_hp < 0)
        return 0;
    return act_hp;
}

void display_health_bar(sfRenderWindow *window, sprite_t *sprites,
    combat_t *info)
{
    double act_hp = 0;
    sfVector2f ratio = {0, 0};

    for (int i = 0; i < NB_ENTITY_SQUAD * 2; ++i) {
        if (info->field[i] != NULL) {
            change_hp_pos(info, sprites, i);
            act_hp = get_actual_hp(info->field[i]);
            ratio = (sfVector2f){(act_hp / info->field[i]->stats->hp)
                * 0.5, 1 * 0.75};
            sfSprite_setRotation(sprites[RED_BAR].sprite, -90);
            sfSprite_setRotation(sprites[GREEN_BAR].sprite, -90);
            sfSprite_setScale(sprites[RED_BAR].sprite,
                (sfVector2f){0.5, 0.75});
            sfSprite_setScale(sprites[GREEN_BAR].sprite, ratio);
            sfRenderWindow_drawSprite(window, sprites[HP_BAR_1].sprite, NULL);
            sfRenderWindow_drawSprite(window, sprites[RED_BAR].sprite, NULL);
            sfRenderWindow_drawSprite(window, sprites[GREEN_BAR].sprite, NULL);
        }
    }
}
