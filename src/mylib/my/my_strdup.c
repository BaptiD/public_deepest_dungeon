/*
** EPITECH PROJECT, 2024
** my_strdup
** File description:
** description
*/

#include <stdlib.h>
#include "my.h"

char *my_strdup(char const *src)
{
    char *dest;
    int k;
    int len = my_strlen((char *)src);

    dest = malloc(sizeof(char) * (len + 1));
    if (!dest)
        return NULL;
    for (k = 0; k < len; k++) {
        dest[k] = src[k];
    }
    dest[k] = '\0';
    return dest;
}
