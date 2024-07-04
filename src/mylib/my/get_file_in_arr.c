/*
** EPITECH PROJECT, 2024
** B-MUL-200-PAR-2-1-myrpg-pierre.pruvost
** File description:
** get_file_in_arr.c
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static int get_nb_lines(char const *filepath)
{
    FILE *stream = fopen(filepath, "r");
    int nb_lines = 0;
    char *line = NULL;
    size_t size;

    if (stream == NULL) {
        return -1;
    }
    while (getline(&line, &size, stream) != -1)
        if (line[0] != '\n')
            nb_lines += 1;
    fclose(stream);
    return nb_lines;
}

static char *dup_line(char *line)
{
    char *new_line = malloc(sizeof(char) * strlen(line));

    if (new_line == NULL) {
        return NULL;
    }
    for (int i = 0; line[i] != '\0' && line[i] != '\n'; ++i)
        new_line[i] = line[i];
    new_line[strlen(line) - 1] = '\0';
    return new_line;
}

char **get_file_as_arr(char const *filepath)
{
    char **file = NULL;
    FILE *stream = NULL;
    char *line = NULL;
    size_t size = 0;
    int nb_lines = get_nb_lines(filepath);

    if (nb_lines <= 0)
        return NULL;
    stream = fopen(filepath, "r");
    file = malloc(sizeof(char *) * (nb_lines + 1));
    if (file == NULL) {
        return NULL;
    }
    for (int i = 0; getline(&line, &size, stream) != -1; ++i)
        file[i] = dup_line(line);
    free(line);
    file[nb_lines] = NULL;
    return file;
}
