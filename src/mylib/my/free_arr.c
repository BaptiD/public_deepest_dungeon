/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** lib/my/free_arr.c
*/

#include <stddef.h>
#include <stdlib.h>

void free_arr(char **arr)
{
    for (int i = 0; arr[i] != NULL; ++i)
        free(arr[i]);
    free(arr);
}
