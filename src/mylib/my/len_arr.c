/*
** EPITECH PROJECT, 2024
** B-MUL-200-PAR-2-1-myrpg-pierre.pruvost
** File description:
** len_arr.c
*/
#include <stddef.h>

int len_arr(char **arr)
{
    int i;

    for (i = 0; arr[i] != NULL; ++i);
    return i;
}
