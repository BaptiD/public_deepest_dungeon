/*
** EPITECH PROJECT, 2024
** B-MUL-200-PAR-2-1-myrpg-pierre.pruvost
** File description:
** main_event.c
*/
#include "combat.h"
#include "capacity.h"

static void combat_mouse_click(display_t *display, combat_t *info)
{
    sfVector2i pos = sfMouse_getPositionRenderWindow(display->window);
}

static void keyboard_focus_event(display_t *display, combat_t *info)
{
    if (info->capa_pressed == 0)
        return;
    play_sound(display->sounds[HOVER_WAV]);
    for (int num_key = sfKeyNum1; num_key <= sfKeyNum8; ++num_key) {
        if (sfKeyboard_isKeyPressed(num_key) &&
            can_focus(info, num_key - 27) == sfTrue)
            capacity_event(display, info, info->capa_pressed, num_key - 27);
        if (sfKeyboard_isKeyPressed(num_key) &&
            can_focus(info, num_key - 27) == sfFalse)
            play_sound(display->sounds[WRONG_WAV]);
    }
}

static void combat_keyboard_click(display_t *display, combat_t *info,
    int *run_game)
{
    if (sfKeyboard_isKeyPressed(sfKeyEscape))
        pause_menu(display, run_game);
    if (info->turn >= NB_ENTITY_SQUAD)
        return;
    if (sfKeyboard_isKeyPressed(sfKeyA) &&
        position_capa(info, info->field[info->turn], CAPA_1) == sfTrue)
        info->capa_pressed = CAPA_1;
    if (sfKeyboard_isKeyPressed(sfKeyZ) &&
        position_capa(info, info->field[info->turn], CAPA_2) == sfTrue)
        info->capa_pressed = CAPA_2;
    if (sfKeyboard_isKeyPressed(sfKeyE) &&
        position_capa(info, info->field[info->turn], CAPA_3) == sfTrue)
        info->capa_pressed = CAPA_3;
    if (sfKeyboard_isKeyPressed(sfKeyR) &&
        position_capa(info, info->field[info->turn], CAPA_4) == sfTrue)
        info->capa_pressed = CAPA_4;
    keyboard_focus_event(display, info);
}

void combat_event_manager(display_t *display, combat_t *info, int *run_game,
    int *run_combat)
{
    sfEvent event;

    while (sfRenderWindow_pollEvent(display->window, &event)) {
        if (event.type == sfEvtClosed)
            sfRenderWindow_close(display->window);
        if (event.type == sfEvtMouseButtonPressed)
            combat_mouse_click(display, info);
        if (event.type == sfEvtKeyPressed)
            combat_keyboard_click(display, info, run_game);
    }
    if (*run_game == false)
        *run_combat = false;
}
