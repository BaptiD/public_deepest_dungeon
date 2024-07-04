/*
** EPITECH PROJECT, 2024
** combat tuto
** File description:
** funtions to manage combat during tuto
*/

#include "entity.h"
#include "game.h"
#include "combat.h"
#include "tuto.h"

static void end_combat_tuto(combat_t *info, entity_t *player, display_t *display)
{
    sfMusic_pause(display->sounds[COMBAT_MUSIC_WAV]);
    play_sound(display->sounds[BG_MUSIC_WAV]);
    clear_combat(info, player->id);
}

int combat_loop_tuto(display_t *display, entity_t *player, int boss,
    pnj_t *pnj)
{
    entity_t *monster = set_monster_squad(player, boss);
    combat_t *info = set_combat(player, monster);
    int run_game = true;
    int run_combat = true;

    combat_arrival(info, display);
    next_turn(display, info);
    dialogue_combat_tuto(display, player, pnj, info);
    while (sfRenderWindow_isOpen(display->window) && run_combat == true &&
        is_combat_finished(info, player, display) != sfTrue) {
        combat_event_manager(display, info, &run_game, &run_combat);
        if (info->turn >= NB_ENTITY_SQUAD)
            monster_capacity_event(display, info);
        clock_restart(info);
        anim_idle_field(info);
        draw_combat(display, info);
        sfRenderWindow_display(display->window);
    }
    end_combat_tuto(info, player, display);
    return run_game;
}
