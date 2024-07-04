/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** map_generation/get_map_from_file.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "my.h"
#include "maps.h"

static int is_wrong_line(char *line)
{
    if (strlen(line) < 3) {
        logs(ERROR, "Line error setting map");
        return 0;
    }
    return 1;
}

static int get_length_y_from_file(char const *filepath)
{
    FILE *stream = fopen(filepath, "r");
    int nb_lines = 0;
    char *line = NULL;
    size_t size;

    if (stream == NULL) {
        logs(ERROR, "Could not open map file");
        return -1;
    }
    while (getline(&line, &size, stream) != -1)
        nb_lines += 1;
    fclose(stream);
    return nb_lines;
}

static char *dup_line(char *line)
{
    char *new_line = malloc(sizeof(char) * strlen(line));

    if (new_line == NULL) {
        logs(ERROR, "Malloc failed");
        return NULL;
    }
    for (int i = 0; line[i] != '\0' && line[i] != '\n'; ++i)
        new_line[i] = line[i];
    new_line[strlen(line) - 1] = '\0';
    return new_line;
}

static char **read_file(FILE *stream, int length_y)
{
    char **map = malloc(sizeof(char *) * (length_y + 1));
    char *line = NULL;
    size_t size;

    for (int i = 0; getline(&line, &size, stream) != -1; ++i) {
        if (is_wrong_line(line) == 0)
            return NULL;
        map[i] = dup_line(line);
        if (map[i] == NULL)
            return NULL;
    }
    map[length_y] = NULL;
    free(line);
    return map;
}

char **get_boss_file(int map_enum)
{
    FILE *stream = NULL;
    char **map = NULL;
    int length_y = get_length_y_from_file(BOSS_FILEPATH[map_enum]);

    stream = fopen(BOSS_FILEPATH[map_enum], "r");
    if (stream == NULL || length_y <= 2) {
        logs(ERROR, "Wrong map reading");
        return NULL;
    }
    map = read_file(stream, length_y);
    fclose(stream);
    return map;
}

char **get_map_from_file(int map_enum)
{
    FILE *stream = NULL;
    char **map = NULL;
    int length_y = get_length_y_from_file(MAPS_FILEPATH[map_enum]);

    stream = fopen(MAPS_FILEPATH[map_enum], "r");
    if (stream == NULL || length_y <= 2) {
        logs(ERROR, "Wrong map reading");
        return NULL;
    }
    map = read_file(stream, length_y);
    fclose(stream);
    return map;
}
