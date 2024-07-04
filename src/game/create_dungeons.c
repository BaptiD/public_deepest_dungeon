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

bool is_good_room(room_t room, const room_t directions[], status_t status)
{
    for (size_t i = 0; status == NO_DOOR && i < NUMBER_ROOMS; i++)
        if (room == directions[i]) {
            return false;
        }
    for (size_t i = 0; status == IS_DOOR && i < NUMBER_ROOMS; i++)
        if (room == directions[i]) {
            return true;
        }
    if (status == IS_DOOR) {
        return false;
    }
    return true;
}

static void where_to_go(room_t rooms[21][21], size_t *x, size_t *y)
{
    bool moved = false;
    int nb = 0;

    for (size_t i = 0; moved == false; i++) {
        nb = get_random_nb(1, 4);
        moved = make_a_bad_move(rooms, x, y, nb);
        if (moved == false)
            moved = make_a_good_move(rooms, x, y, nb);
        if (i == 100) {
            rooms[*y][*x] = ROOM_ALL;
        }
    }
}

static void where_can_go(room_t rooms[21][21], size_t x,
    size_t y, status_t status[4])
{
    LEFT_ST = MAY_DOOR;
    TOP_ST = MAY_DOOR;
    RIGHT_ST = MAY_DOOR;
    BOT_ST = MAY_DOOR;
    if (is_good_room(rooms[y][x - 1], right_door, IS_DOOR) == true &&
        rooms[y][x - 1] != NO_ROOM)
        LEFT_ST = IS_DOOR;
    if (is_good_room(rooms[y - 1][x], bot_door, IS_DOOR) == true &&
        rooms[y - 1][x] != NO_ROOM)
        TOP_ST = IS_DOOR;
    if (is_good_room(rooms[y][x + 1], left_door, IS_DOOR) == true &&
        rooms[y][x + 1] != NO_ROOM)
        RIGHT_ST = IS_DOOR;
    if (is_good_room(rooms[y + 1][x], top_door, IS_DOOR) == true &&
        rooms[y + 1][x] != NO_ROOM)
        BOT_ST = IS_DOOR;
}

static void where_can_not_go(room_t rooms[21][21], size_t x,
    size_t y, status_t status[4])
{
    if (is_good_room(rooms[y][x - 1], right_door, NO_DOOR) == true &&
        rooms[y][x - 1] != NO_ROOM)
        LEFT_ST = NO_DOOR;
    if (is_good_room(rooms[y - 1][x], bot_door, NO_DOOR) == true &&
        rooms[y - 1][x] != NO_ROOM)
        TOP_ST = NO_DOOR;
    if (is_good_room(rooms[y][x + 1], left_door, NO_DOOR) == true &&
        rooms[y][x + 1] != NO_ROOM)
        RIGHT_ST = NO_DOOR;
    if (is_good_room(rooms[y + 1][x], top_door, NO_DOOR) == true &&
        rooms[y + 1][x] != NO_ROOM)
        BOT_ST = NO_DOOR;
}

static void set_rooms(room_t rooms[21][21])
{
    status_t status[4] = {MAY_DOOR, MAY_DOOR, MAY_DOOR, MAY_DOOR};
    size_t x = 10;
    size_t y = 10;

    rooms[y][x] = get_room(status, ONE_DOOR_START, ONE_DOOR_END);
    for (size_t count_rooms = 0; count_rooms < 8; count_rooms++) {
        where_to_go(rooms, &x, &y);
        where_can_go(rooms, x, y, status);
        where_can_not_go(rooms, x, y, status);
        rooms[y][x] = get_room(status, TWO_DOOR_START, THREE_DOOR_END);
    }
}

static bool has_a_neighboor(room_t rooms[21][21], size_t x, size_t y)
{
    if (rooms[y][x - 1] != NO_ROOM)
        return true;
    if (rooms[y - 1][x] != NO_ROOM)
        return true;
    if (rooms[y][x + 1] != NO_ROOM)
        return true;
    if (rooms[y + 1][x] != NO_ROOM)
        return true;
    return false;
}

static void end_path(room_t rooms[21][21], size_t x,
    size_t y, status_t status[4])
{
    LEFT_ST = NO_DOOR;
    TOP_ST = NO_DOOR;
    RIGHT_ST = NO_DOOR;
    BOT_ST = NO_DOOR;
    if (is_good_room(rooms[y][x - 1], right_door, IS_DOOR) == true &&
        rooms[y][x - 1] != NO_ROOM)
        LEFT_ST = IS_DOOR;
    if (is_good_room(rooms[y - 1][x], bot_door, IS_DOOR) == true &&
        rooms[y - 1][x] != NO_ROOM)
        TOP_ST = IS_DOOR;
    if (is_good_room(rooms[y][x + 1], left_door, IS_DOOR) == true &&
        rooms[y][x + 1] != NO_ROOM)
        RIGHT_ST = IS_DOOR;
    if (is_good_room(rooms[y + 1][x], top_door, IS_DOOR) == true &&
        rooms[y + 1][x] != NO_ROOM)
        BOT_ST = IS_DOOR;
}

static void end_room(room_t rooms[21][21], size_t x, size_t y,
    status_t status[4])
{
    if (has_a_neighboor(rooms, x, y) == true) {
        end_path(rooms, x, y, status);
        rooms[y][x] = get_room(status, ONE_DOOR_START, ROOM_ALL);
    }
}

static void set_ends(room_t rooms[21][21])
{
    status_t status[4] = {NO_DOOR, NO_DOOR, NO_DOOR, NO_DOOR};

    for (size_t y = 1; y < 20; y++) {
        for (size_t x = 1; x < 20; x++) {
            end_room(rooms, x, y, status);
        }
    }
}

void generate_room(room_t rooms[21][21])
{
    set_empty_map(rooms);
    set_rooms(rooms);
    set_ends(rooms);
}
