/*
** EPITECH PROJECT, 2024
** B-MUL-200-PAR-2-1-myrpg-pierre.pruvost
** File description:
** display_capacities.c
*/

#include "capacity.h"
#include "combat.h"

static void display_capa_selected(display_t *display, combat_t *info,
    int i)
{
    if (info->capa_pressed - 3 == i) {
        sfSprite_setPosition(display->tab[TURN_CHOOSE].sprite,
            (sfVector2f){CAPA_POS_COMBAT[i].x - 18,
            CAPA_POS_COMBAT[i].y + 80});
        sfRenderWindow_drawSprite(display->window,
            display->tab[TURN_CHOOSE].sprite, NULL);
    }
}

static sfBool is_position_good(int i, entity_t *entity, int capa)
{
    if (capa >= 0 && CAPACITY[entity->capacities[capa]].range[i] == 1)
        return sfTrue;
    return sfFalse;
}

static sfBool is_focus_good(int i, entity_t *entity, int capa)
{
    if (capa >= 0 && CAPACITY[entity->capacities[capa]].focus[i] == 1)
        return sfTrue;
    return sfFalse;
}

static void display_focus(display_t *display, combat_t *info, int i)
{
    for (int i = 0; i < NB_ENTITY_SQUAD; ++i) {
        if (is_focus_good(i + NB_ENTITY_SQUAD, info->field[info->turn],
            info->capa_pressed - 3) == sfTrue) {
            sfSprite_setPosition(display->tab[CAN_FOCUS].sprite,
                (sfVector2f){CAPA_INDI_X + (CAPA_INDI_SEPARATOR *
                (i + NB_ENTITY_SQUAD)) + CAPA_INDI_SEPARATOR, CAPA_INDI_Y});
            sfRenderWindow_drawSprite(display->window,
                display->tab[CAN_FOCUS].sprite, NULL);
        } else {
            sfSprite_setPosition(display->tab[CANT_FOCUS].sprite,
                (sfVector2f){CAPA_INDI_X + (CAPA_INDI_SEPARATOR *
                (i + NB_ENTITY_SQUAD)) + CAPA_INDI_SEPARATOR, CAPA_INDI_Y});
            sfRenderWindow_drawSprite(display->window,
                display->tab[CANT_FOCUS].sprite, NULL);
        }
    }
}

static void display_range(display_t *display, combat_t *info, int i)
{
    for (int i = 0; i < NB_ENTITY_SQUAD; ++i) {
        if (is_position_good(i, info->field[info->turn],
            info->capa_pressed - 3) == sfTrue) {
            sfSprite_setPosition(display->tab[CAN_RANGE].sprite,
                (sfVector2f){CAPA_INDI_X + (CAPA_INDI_SEPARATOR * i),
                CAPA_INDI_Y});
            sfRenderWindow_drawSprite(display->window,
                display->tab[CAN_RANGE].sprite, NULL);
        } else {
            sfSprite_setPosition(display->tab[CANT_RANGE].sprite,
                (sfVector2f){CAPA_INDI_X + (CAPA_INDI_SEPARATOR * i),
                CAPA_INDI_Y});
            sfRenderWindow_drawSprite(display->window,
                display->tab[CANT_RANGE].sprite, NULL);
        }
    }
}

void display_capacities_combat(display_t *display, combat_t *info)
{
    sfSprite *capa = sfSprite_create();
    sfTexture *texture = NULL;

    sfSprite_setScale(capa, (sfVector2f){5, 5});
    for (int i = 0; i < NB_CAPA_BY_ENTITY; ++i) {
        texture = sfTexture_createFromFile(CAPA_DISP_PATH
            [info->field[info->turn]->capacities[i]], NULL);
        sfSprite_setTexture(capa, texture, sfTrue);
        sfSprite_setPosition(capa, CAPA_POS_COMBAT[i]);
        sfRenderWindow_drawSprite(display->window, capa, NULL);
        sfTexture_destroy(texture);
        display_range(display, info, i);
        display_focus(display, info, i);
        display_capa_selected(display, info, i);
    }
    sfSprite_destroy(capa);
}
