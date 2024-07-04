/*
** EPITECH PROJECT, 2024
** pnj
** File description:
** functions to manage_pnj
*/

#include <stdio.h>
#include <stdbool.h>

#include "entity.h"
#include "game.h"
#include "combat.h"
#include "my.h"

static pnj_t *find_pnj(dungeon_t *dungeon)
{
    maps_t map = ACTUAL_MAP;

    for (size_t i = 0; i < NB_PNJ; i++) {
        if (dungeon->pnjs[i]->co_room.x == map.co_map.x &&
            dungeon->pnjs[i]->co_room.y == map.co_map.y)
            return dungeon->pnjs[i];
    }
    return NULL;
}

bool is_close_to_pnj(pnj_t *pnj, entity_t *play)
{
    if (pnj->pos[0] == play->pos[0] && (pnj->pos[1] + 1 == play->pos[1] ||
        pnj->pos[1] - 1 == play->pos[1]))
        return true;
    if (pnj->pos[0] + 1 == play->pos[0] && (pnj->pos[1] + 1 == play->pos[1] ||
        pnj->pos[1] - 1 == play->pos[1] || pnj->pos[1] == play->pos[1]))
        return true;
    if (pnj->pos[0] - 1 == play->pos[0] && (pnj->pos[1] + 1 == play->pos[1] ||
        pnj->pos[1] - 1 == play->pos[1] || pnj->pos[1] == play->pos[1]))
        return true;
    return false;
}

static void set_next_dialogue(pnj_t *pnj)
{
    if (pnj->dialogue[pnj->dialogue_line + 1] == NULL)
        return;
    else {
        pnj->dialogue_line++;
        pnj->text[DIALOGUE]->dialogue = pnj->dialogue[pnj->dialogue_line];
        sfText_setString(pnj->text[DIALOGUE]->text, pnj->text[DIALOGUE]->dialogue);
    }
}

static void dialogue_if_squad_full(pnj_t *pnj, display_t *display,
    entity_t *player, int *run_game)
{
    if (my_strcmp(pnj->text[DIALOGUE]->dialogue, DIALOGUE_SQUAD_FULL) != 0) {
        pnj->text[DIALOGUE]->dialogue = DIALOGUE_SQUAD_FULL;
        sfText_setString(pnj->text[DIALOGUE]->text, pnj->text[DIALOGUE]->dialogue);
    }
    if (sfKeyboard_isKeyPressed(sfKeySpace))
        pnj->is_talking = false;
}

static void dialogue_if_squad_not_full(pnj_t *pnj, display_t *display,
    entity_t *player, int *run_game)
{
    if (sfKeyboard_isKeyPressed(sfKeySpace))
        set_next_dialogue(pnj);
    if (sfKeyboard_isKeyPressed(sfKeyY) &&
        pnj->dialogue[pnj->dialogue_line + 1] == NULL) {
        add_pnj_to_squad(player, pnj);
        combat_loop(display, player, NO_BOSS, run_game);
        pnj->is_talking = false;
        pnj->status_quest = DONE;
    }
    if (sfKeyboard_isKeyPressed(sfKeyN) &&
        pnj->dialogue[pnj->dialogue_line + 1] == NULL) {
        pnj->is_talking = false;
        pnj->dialogue_line = 0;
        pnj->text[DIALOGUE]->dialogue = pnj->dialogue[pnj->dialogue_line];
    }
    pnj->text[DIALOGUE]->dialogue = pnj->dialogue[pnj->dialogue_line];
    sfText_setString(pnj->text[DIALOGUE]->text, pnj->text[DIALOGUE]->dialogue);
}

static void manage_keyboard_click(pnj_t *pnj, display_t *display,
    entity_t *player, int *run_game)
{
    if (squad_size(player) == 4)
        dialogue_if_squad_full(pnj, display, player, run_game);
    else
        dialogue_if_squad_not_full(pnj, display, player, run_game);
}

static void manage_dialogue(pnj_t *pnj, display_t *display, entity_t *player,
    int *run_game)
{
    sfEvent event;

    while (sfRenderWindow_pollEvent(display->window, &event)) {
        if (event.type == sfEvtClosed)
            sfRenderWindow_close(display->window);
        if (event.type == sfEvtKeyPressed)
            manage_keyboard_click(pnj, display, player, run_game);
    }
}

void display_dialogue(dungeon_t *dungeon, entity_t *player,
    display_t *display, pnj_t *pnj)
{
    display_map(display, dungeon);
    player->rect = display_entity(display->window, player->clock,
        player->display[EXPLO_STATE], player->rect);
    sfRenderWindow_drawSprite(display->window,
        pnj->display[COMBAT_STATE]->sprite, NULL);
    sfRenderWindow_drawSprite(display->window, pnj->text[DIALOGUE]->sprite->sprite,
        NULL);
    sfRenderWindow_drawText(display->window, pnj->text[NAME]->text, NULL);
    sfRenderWindow_drawText(display->window, pnj->text[DIALOGUE]->text, NULL);
    sfRenderWindow_display(display->window);
    sfRenderWindow_clear(display->window, BG_DEFAULT_COLOR);
}

static void dialogue(dungeon_t *d, entity_t *p, display_t *display,
    int *run_game)
{
    sfEvent e;
    pnj_t *pnj = find_pnj(d);

    sfSprite_setPosition(pnj->display[COMBAT_STATE]->sprite,
        (sfVector2f){0, 400});
    sfSprite_setScale(pnj->display[COMBAT_STATE]->sprite, (sfVector2f){4, 4});
    while (sfRenderWindow_isOpen(display->window) && pnj->is_talking == true &&
        pnj->status_quest != DONE) {
        manage_dialogue(pnj, display, p, run_game);
        display_dialogue(d, p, display, pnj);
    }
    sfSprite_setScale(pnj->display[COMBAT_STATE]->sprite, (sfVector2f){3, 3});
}

void manage_pnj(dungeon_t *dungeon, entity_t *p, display_t *display, int *run_game)
{
    pnj_t *pnj = find_pnj(dungeon);

    if (pnj == NULL)
        return;
    if (sfKeyboard_isKeyPressed(sfKeyE)) {
        if (is_close_to_pnj(pnj, p) == true && pnj->status_quest == NOT_DONE) {
            pnj->is_talking = true;
            pnj->rect = (sfIntRect){0, 0,
                COMBAT_ANIMATION[pnj->type]->frame_x,
                COMBAT_ANIMATION[pnj->type]->y_max};
            sfSprite_setTextureRect(pnj->display[COMBAT_STATE]->sprite, pnj->rect);
            dialogue(dungeon, p, display, run_game);
        }
    }
    if (pnj->status_quest == DONE)
        ACTUAL_MAP.char_map[pnj->pos[0]][pnj->pos[1]] = ' ';
}
