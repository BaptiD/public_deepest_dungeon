/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** my.h
*/
#ifndef MY_H_
    #define MY_H_
    #include "SFML/System.h"

    #define INFO 0
    #define SUCCESS 1
    #define ERROR -1

////////////// CLOCK //////////////

typedef struct my_clock_s {
    sfClock *time;
    int index;
} my_clock_t;

////////////// FUNCTIONS //////////////

void free_arr(char **arr);
char **my_str_to_word_arr(char const *str, char c);
void logs(int status, char *line);
void setup_logs_file(void);
int check_env(char **env);
int len_arr(char **arr);
char **get_file_as_arr(char const *filepath);
char *my_strdup(char const *src);
int my_strlen(char *str);
int my_strcmp(char *s1, char *s2);
my_clock_t *set_clock(void);
void destory_clock(my_clock_t *clock);
sfBool time_elapsed(sfClock *clock, double check_time);

#endif
