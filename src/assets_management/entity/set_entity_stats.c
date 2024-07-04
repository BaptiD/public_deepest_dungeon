/*
** EPITECH PROJECT, 2024
** B-MUL-200-PAR-2-1-myrpg-pierre.pruvost
** File description:
** set_entity_stats.c
*/

#include "entity.h"
#include "my.h"

stats_t *set_stats(char *line)
{
    char **line_arr = my_str_to_word_arr(line, ';');
    stats_t *stats = NULL;

    if (len_arr(line_arr) != 6) {
        logs(ERROR, "Wrong line entity stats");
        free_arr(line_arr);
        return NULL;
    }
    stats = malloc(sizeof(stats_t));
    stats->atk = atoi(line_arr[0]);
    stats->hp = atoi(line_arr[1]);
    stats->spd = atoi(line_arr[2]);
    stats->crt = atoi(line_arr[3]);
    stats->pre = atoi(line_arr[4]);
    stats->pro = atoi(line_arr[5]);
    free_arr(line_arr);
    return stats;
}

stats_t *set_mod_empty(void)
{
    stats_t *stats = malloc(sizeof(stats_t));

    stats->atk = 0;
    stats->hp = 0;
    stats->spd = 0;
    stats->crt = 0;
    stats->pre = 0;
    stats->pro = 0;
    return stats;
}

effects_t set_empty_effects(void)
{
    effects_t effects = {0};

    effects.stun[NB_TURN_EFFECT] = 0;
    effects.stun[DAMAGES_EFFECT] = 0;
    effects.bleed[NB_TURN_EFFECT] = 0;
    effects.bleed[DAMAGES_EFFECT] = 0;
    effects.burn[NB_TURN_EFFECT] = 0;
    effects.burn[DAMAGES_EFFECT] = 0;
    effects.poison[NB_TURN_EFFECT] = 0;
    effects.poison[DAMAGES_EFFECT] = 0;
    return effects;
}
