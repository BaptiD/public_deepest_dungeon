/*
** EPITECH PROJECT, 2024
** B-MUL-200-PAR-2-1-myrpg-pierre.pruvost
** File description:
** env_check.c
*/
#include "my.h"
#include "statics.h"
#include <string.h>
#include <stdlib.h>

int check_env(char **env)
{
    char **line = NULL;

    logs(INFO, "Checking environment...");
    if (env == NULL) {
        logs(ERROR, "Environment missing");
        return 84;
    }
    logs(SUCCESS, "Environment OK");
    logs(INFO, "Checking display...");
    for (int k = 0; env[k] != NULL; k++) {
        line = my_str_to_word_arr(env[k], '=');
        if (strcmp(line[0], "DISPLAY") == 0) {
            logs(SUCCESS, "Display OK");
            return 0;
        }
    }
    free(line);
    logs(ERROR, "Display missing");
    return 84;
}
