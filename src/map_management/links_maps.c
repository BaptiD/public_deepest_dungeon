/*
** EPITECH PROJECT, 2024
** B-MUL-200-PAR-2-1-myrpg-pierre.pruvost
** File description:
** links_maps.c
*/
#include "maps.h"
#include "my.h"
#include "statics.h"

#include <string.h>
#include <stdlib.h>

static int nb_char_in_line(char *line, char c)
{
    int nb_char = 0;

    for (int i = 0; line[i] != '\0'; ++i)
        if (line[i] == c)
            nb_char += 1;
    return nb_char;
}

static int get_nb_door_map(char **maps)
{
    int nb_door = 0;

    for (int x = 0; maps[x] != NULL; ++x)
        nb_door = nb_char_in_line(maps[x], 'D');
    return nb_door;
}
