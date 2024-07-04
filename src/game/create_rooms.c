/*
** EPITECH PROJECT, 2024
** create_dungeons
** File description:
** functions to create the whole dungeon
*/

#include <stdio.h>
#include "creation.h"
#include <stdbool.h>
#include <stdlib.h>

int get_random_nb(int n, int m)
{
    int random_nb = 0;

    if (m < n)
        return -1;
    random_nb = arc4random() % (m - n + 1);
    random_nb += n;
    return random_nb;
}

void set_empty_map(room_t rooms[21][21])
{
    for (size_t i = 0; i <= 20; i++) {
        for (size_t j = 0; j <= 20; j++) {
            rooms[i][j] = NO_ROOM;
        }
    }
}

room_t get_room(status_t status[4], room_t start, room_t end)
{
    room_t room = get_random_nb(start, end);

    if (is_good_room(room, left_door, LEFT_ST) == false)
        return (get_room(status, start, end));
    if (is_good_room(room, top_door, TOP_ST) == false)
        return (get_room(status, start, end));
    if (is_good_room(room, right_door, RIGHT_ST) == false)
        return (get_room(status, start, end));
    if (is_good_room(room, bot_door, BOT_ST) == false)
        return (get_room(status, start, end));
    return room;
}

bool make_a_good_move(room_t rooms[21][21], size_t *x,
    size_t *y, int nb)
{
    if (nb == 3 && is_good_room(rooms[*y][*x], right_door, IS_DOOR) == true &&
        rooms[*y][*x + 1] == NO_ROOM) {
        *x += 1;
        return true;
    }
    if (nb == 4 && is_good_room(rooms[*y][*x], bot_door, IS_DOOR) == true &&
        rooms[*y + 1][*x] == NO_ROOM) {
        *y += 1;
        return true;
    }
    return false;
}

bool make_a_bad_move(room_t rooms[21][21], size_t *x,
    size_t *y, int nb)
{
    if (nb == 1 && is_good_room(rooms[*y][*x], left_door, IS_DOOR) == true &&
        rooms[*y][*x - 1] == NO_ROOM) {
        *x -= 1;
        return true;
    }
    if (nb == 2 && is_good_room(rooms[*y][*x], top_door, IS_DOOR) == true &&
        rooms[*y - 1][*x] == NO_ROOM) {
        *y -= 1;
        return true;
    }
    return false;
}
