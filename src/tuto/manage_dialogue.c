/*
** EPITECH PROJECT, 2024
** manage_dialogue
** File description:
** functions to mnage dialogue with pnj
*/

#include "game.h"
#include "maps.h"
#include "entity.h"
#include "combat.h"
#include "tuto.h"

static void set_next_dialogue(pnj_t *pnj)
{
    if (pnj->dialogue[pnj->dialogue_line + 1] == NULL)
        return;
    else {
        pnj->dialogue_line++;
        pnj->text[DIALOGUE]->dialogue = pnj->dialogue[pnj->dialogue_line];
        sfText_setString(pnj->text[DIALOGUE]->text,
            pnj->text[DIALOGUE]->dialogue);
    }
}

static void set_pos_text_fight(pnj_t *pnj)
{
    sfVector2f pos;

    sfSprite_setPosition(pnj->text[DIALOGUE]->sprite->sprite,
        (sfVector2f){0, 100});
    sfText_setPosition(pnj->text[DIALOGUE]->text, (sfVector2f){100, 170});
    pos = sfSprite_getPosition(pnj->text[DIALOGUE]->sprite->sprite);
    pos.x += 180;
    pos.y += 15;
    sfText_setPosition(pnj->text[NAME]->text, pos);
}

static void reset_pos_text(pnj_t *pnj)
{
    sfVector2f pos;

    sfSprite_setPosition(pnj->text[DIALOGUE]->sprite->sprite,
        (sfVector2f){0, 765});
    sfText_setPosition(pnj->text[DIALOGUE]->text, (sfVector2f){100, 830});
    pos = sfSprite_getPosition(pnj->text[DIALOGUE]->sprite->sprite);
    pos.x += 180;
    pos.y += 15;
    sfText_setPosition(pnj->text[NAME]->text, pos);
}

static void dialogue_before(pnj_t *pnj, display_t *display,
    entity_t *player, sfEvent e)
{
    if (e.type == sfEvtKeyPressed && sfKeyboard_isKeyPressed(sfKeySpace) &&
        (pnj->dialogue_line < ID_DIALOGUE_TUTO_START))
        set_next_dialogue(pnj);
    if (e.type == sfEvtKeyPressed && sfKeyboard_isKeyPressed(sfKeyY) &&
        pnj->dialogue_line == ID_DIALOGUE_TUTO_START) {
        set_pos_text_fight(pnj);
        set_next_dialogue(pnj);
        add_pnj_to_squad(player, pnj);
        sfMusic_pause(display->sounds[BG_MUSIC_WAV]);
        combat_loop_tuto(display, player, NO_BOSS, pnj);
        pnj->status_quest = DONE;
        reset_pos_text(pnj);
    }
    if (e.type == sfEvtKeyPressed && sfKeyboard_isKeyPressed(sfKeyN) &&
        pnj->dialogue_line == ID_DIALOGUE_TUTO_START) {
        pnj->dialogue_line = ID_DIALOGUE_NO_TUTO;
        pnj->status_quest = DONE;
    }
    pnj->text[DIALOGUE]->dialogue = pnj->dialogue[pnj->dialogue_line];
    sfText_setString(pnj->text[DIALOGUE]->text, pnj->text[DIALOGUE]->dialogue);
}

static void dialogue_after(pnj_t *pnj, display_t *display,
    entity_t *player, sfEvent e)
{
    if (e.type == sfEvtKeyPressed && sfKeyboard_isKeyPressed(sfKeySpace) &&
        (pnj->dialogue_line < ID_DIALOGUE_NO_TUTO))
        set_next_dialogue(pnj);
    if (e.type == sfEvtKeyPressed && sfKeyboard_isKeyPressed(sfKeySpace) &&
        (pnj->dialogue_line + 1 >= ID_DIALOGUE_NO_TUTO))
        pnj->is_talking = false;
    pnj->text[DIALOGUE]->dialogue = pnj->dialogue[pnj->dialogue_line];
    sfText_setString(pnj->text[DIALOGUE]->text, pnj->text[DIALOGUE]->dialogue);
}

int dialogue_in_combat(display_t *display, entity_t *player, pnj_t *pnj,
    sfEvent e)
{
    while (sfRenderWindow_pollEvent(display->window, &e)) {
        if (e.type == sfEvtClosed)
            sfRenderWindow_close(display->window);
        if (e.type == sfEvtKeyPressed && sfKeyboard_isKeyPressed(sfKeySpace) &&
            pnj->dialogue_line < ID_DIALOGUE_TUTO_END)
            set_next_dialogue(pnj);
        if (e.type == sfEvtKeyPressed && sfKeyboard_isKeyPressed(sfKeySpace) &&
            pnj->dialogue_line + 1 > ID_DIALOGUE_TUTO_END)
            return END;
        pnj->text[DIALOGUE]->dialogue = pnj->dialogue[pnj->dialogue_line];
        sfText_setString(pnj->text[DIALOGUE]->text,
            pnj->text[DIALOGUE]->dialogue);
    }
    return IN_PROGRESS;
}

void dialogue_combat_tuto(display_t *display, entity_t *player, pnj_t *pnj,
    combat_t *info)
{
    sfEvent e;

    while (sfRenderWindow_isOpen(display->window)) {
        if (dialogue_in_combat(display, player, pnj, e) == END)
            return;
        clock_restart(info);
        anim_idle_field(info);
        draw_combat(display, info);
        sfRenderWindow_drawSprite(display->window,
            pnj->text[DIALOGUE]->sprite->sprite, NULL);
        sfRenderWindow_drawText(display->window, pnj->text[DIALOGUE]->text,
            NULL);
        sfRenderWindow_drawText(display->window, pnj->text[NAME]->text, NULL);
        sfRenderWindow_display(display->window);
    }
}

void manage_dialogue_tuto(pnj_t *pnj, display_t *display, entity_t *player,
    sfEvent e)
{
    if (e.type == sfEvtClosed)
        sfRenderWindow_close(display->window);
    if (pnj->status_quest == NOT_DONE)
        dialogue_before(pnj, display, player, e);
    else
        dialogue_after(pnj, display, player, e);
}

void dialogue_tuto(dungeon_t *d ,pnj_t *pnj, display_t *display,
    entity_t *player)
{
    sfEvent e;

    while (sfRenderWindow_isOpen(display->window) && pnj->is_talking == true) {
        while (sfRenderWindow_pollEvent(display->window, &e)) {
            manage_dialogue_tuto(pnj, display, player, e);
        }
        display_dialogue(d, player, display, pnj);
    }
}

void manage_pnj_tuto(dungeon_t *d, entity_t *p, display_t *display,
    sprite_t *popup)
{
    pnj_t *pnj = d->pnjs[0];

    if (sfKeyboard_isKeyPressed(sfKeyE)) {
        if (is_close_to_pnj(pnj, p) == true) {
            sfSprite_setScale(pnj->display[COMBAT_STATE]->sprite,
                (sfVector2f){4, 4});
            pnj->is_talking = true;
            pnj->rect = (sfIntRect){0, 0,
                COMBAT_ANIMATION[pnj->type]->frame_x,
                COMBAT_ANIMATION[pnj->type]->y_max};
            sfSprite_setTextureRect(pnj->display[COMBAT_STATE]->sprite,
                pnj->rect);
            dialogue_tuto(d, pnj, display, p);
        }
    }
    sfSprite_setScale(pnj->display[COMBAT_STATE]->sprite, (sfVector2f){3, 3});
}
