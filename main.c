/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** main.c
*/
#include "game.h"
#include "sprites.h"
#include "my.h"

int main(int ac, char **av, char **env)
{
    setup_logs_file();
    if (check_env(env) == 84)
        return 84;
    return game_launcher();
}
