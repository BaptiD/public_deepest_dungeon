/*
** EPITECH PROJECT, 2024
** B-MUL-200-PAR-2-1-myrpg-pierre.pruvost
** File description:
** main_loop.c
*/
#include "my.h"
#include "combat.h"

void clock_restart(combat_t *info)
{
    sfTime time;
    float seconds;

    time = sfClock_getElapsedTime(info->clock);
    seconds = time.microseconds / 1000000.0;
    if (seconds > CLOCK_RESTART) {
        info->index_clock = 0;
        sfClock_restart(info->clock);
    }
}

void combat_loop(display_t *display, entity_t *player, int boss,
    int *run_game)
{
    entity_t *monster = set_monster_squad(player, boss);
    combat_t *info = set_combat(player, monster);
    int run_combat = true;

    logs(INFO, "Combat loop start");
    combat_arrival(info, display);
    while (sfRenderWindow_isOpen(display->window) && run_combat == true &&
        is_combat_finished(info, player, display) != sfTrue) {
        combat_event_manager(display, info, run_game, &run_combat);
        if (info->turn >= NB_ENTITY_SQUAD)
            monster_capacity_event(display, info);
        clock_restart(info);
        anim_idle_field(info);
        draw_combat(display, info);
        sfRenderWindow_display(display->window);
    }
    logs(INFO, "Combat loop end");
    sfMusic_pause(display->sounds[COMBAT_MUSIC_WAV]);
    clear_combat(info, player->id);
}
