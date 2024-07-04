/*
** EPITECH PROJECT, 2024
** my_strcmp
** File description:
** compares 2 strings
*/

#include "my.h"

int my_strcmp(char *s1, char *s2)
{
    int len_s1 = my_strlen(s1);
    int len_s2 = my_strlen(s2);
    int smallest_len = len_s1;

    if (len_s1 > len_s2) {
        smallest_len = len_s2;
    }
    for (int k = 0; k < smallest_len; k++) {
        if (s1[k] != s2[k]) {
            return s1[k] - s2[k];
        }
    }
    return len_s1 - len_s2;
}
