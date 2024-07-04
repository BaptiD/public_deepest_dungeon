/*
** EPITECH PROJECT, 2024
** B-MUL-200-PAR-2-1-myrpg-pierre.pruvost
** File description:
** clock_time.c
*/

#include <SFML/System.h>
#include <stdlib.h>
#include "my.h"

my_clock_t *set_clock(void)
{
    my_clock_t *clock = malloc(sizeof(my_clock_t));

    clock->time = sfClock_create();
    clock->index = 0;
    return clock;
}

void destory_clock(my_clock_t *clock)
{
    sfClock_destroy(clock->time);
    free(clock);
}

sfBool time_elapsed(sfClock *clock, double check_time)
{
    sfTime time = sfClock_getElapsedTime(clock);
    double seconds = time.microseconds / 1000000.0;

    if (seconds < check_time)
        return sfFalse;
    return sfTrue;
}
