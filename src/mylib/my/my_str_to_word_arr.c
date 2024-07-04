/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** lib/my/my_str_to_word_array.c
*/

#include <stdio.h>
#include <stdlib.h>

char *malloc_word(char const *str, int i, int length_word)
{
    int temp = 0;
    char *word = malloc(sizeof(char) * (length_word + 1));

    while (temp < length_word) {
        word[temp] = str[i + temp];
        temp += 1;
    }
    word[temp] = '\0';
    return word;
}

int number_word(char const *str, char c)
{
    int nb_word = 0;

    for (int i = 0; str[i] != '\0'; ++i) {
        if (str[i] == c)
            nb_word += 1;
    }
    return nb_word + 1;
}

static int get_len_word(char const *str, int i, char c)
{
    int length_word = 0;

    while (str[i] != c && str[i] != '\0') {
        length_word += 1;
        i += 1;
    }
    return length_word;
}

char **my_str_to_word_arr(char const *str, char c)
{
    char **tab;
    int where = 0;
    int nb_word = 0;
    char *word;
    int len_word = 0;

    nb_word = number_word(str, c);
    tab = malloc(sizeof(char *) * (nb_word + 1));
    for (int i = 0; str[i] != '\0';) {
        if (str[i] == c)
            i += 1;
        len_word = get_len_word(str, i, c);
        word = malloc_word(str, i, len_word);
        tab[where] = word;
        where += 1;
        i = len_word + i;
    }
    tab[where] = NULL;
    return tab;
}
