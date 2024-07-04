/*
** EPITECH PROJECT, 2024
** destroy_dungeon
** File description:
** functions to free/destroy dungeon
*/

#include "maps.h"

static void destroy_a_pnj(pnj_t *pnj)
{
    free(pnj->name);
    for (size_t i = 0; pnj->dialogue[i] != NULL; i++)
        free(pnj->dialogue[i]);
    free(pnj->dialogue);
    sfText_destroy(pnj->text[DIALOGUE]->text);
    sfTexture_destroy(pnj->text[DIALOGUE]->sprite->texture);
    sfSprite_destroy(pnj->text[DIALOGUE]->sprite->sprite);
    free(pnj->text[DIALOGUE]->sprite);
    free(pnj->text[DIALOGUE]);
    sfTexture_destroy(pnj->display[EXPLO_STATE]->texture);
    sfSprite_destroy(pnj->display[EXPLO_STATE]->sprite);
    sfTexture_destroy(pnj->display[COMBAT_STATE]->texture);
    sfSprite_destroy(pnj->display[COMBAT_STATE]->sprite);
    sfClock_destroy(pnj->clock);
    free(pnj);
}

static void destroy_pnjs(pnj_t **pnjs)
{
    for (int i = 0; i < NB_PNJ; i++) {
        if (pnjs[i] != NULL)
            destroy_a_pnj(pnjs[i]);
    }
    free(pnjs);
}

void destroy_dungeon(dungeon_t *dungeon)
{
    destroy_pnjs(dungeon->pnjs);
    sfTexture_destroy(dungeon->background.texture);
    sfSprite_destroy(dungeon->background.sprite);
    free(dungeon);
}