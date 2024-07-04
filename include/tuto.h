/*
** EPITECH PROJECT, 2024
** tuto
** File description:
** tuto
*/

#ifndef TUTO_H
    #define TUTO_H

    #include "entity.h"
    #include "maps.h"
    #include "sprites.h"
    #include "game.h"
    #include "combat.h"

    #define MAP_TUTO_ID 15
    #define ID_TUTO_PNJ_FILE 10
    #define ID_DIALOGUE_TUTO_START 4
    #define ID_DIALOGUE_TUTO_END 15
    #define ID_DIALOGUE_NO_TUTO 21
    #define IN_PROGRESS 0
    #define END 1

int tuto_loop(display_t *display);
sprite_t *init_popup(void);
dungeon_t *init_tuto(entity_t *player);
int event_listener_tuto(display_t *display, entity_t *player,
    dungeon_t *dungeon, sprite_t *popup);
void manage_pnj_tuto(dungeon_t *d, entity_t *p, display_t *display,
    sprite_t *popup);
void manage_dialogue(pnj_t *pnj, display_t *display, entity_t *player);
void display_tuto(dungeon_t *dungeon, display_t *display, entity_t *player,
    sprite_t *popup);
void display_dialogue(dungeon_t *dungeon, entity_t *player,
    display_t *display, pnj_t *pnj);
int combat_loop_tuto(display_t *display, entity_t *player, int boss,
    pnj_t *pnj);
void dialogue_combat_tuto(display_t *display, entity_t *player, pnj_t *pnj,
    combat_t *info);

#endif
