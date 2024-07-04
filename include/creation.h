/*
** EPITECH PROJECT, 2024
** B-MUL-200-PAR-2-1-myrpg-pierre.pruvost
** File description:
** creation
*/

#include <stdbool.h>

#ifndef CREATION_H_
    #define CREATION_H_
    #define NUMBER_ROOMS 17
    #define LEFT_ST status[0]
    #define TOP_ST status[1]
    #define RIGHT_ST status[2]
    #define BOT_ST status[3]

typedef enum status_e {
    NO_DOOR,
    MAY_DOOR,
    IS_DOOR
} status_t;

typedef enum room_e {
    ROOM_LEFT,
    ROOM_TOP,
    ROOM_RIGHT,
    ROOM_BOT,
    ROOM_LEFT_RIGHT,
    ROOM_TOP_BOT,
    ROOM_LEFT_TOP,
    ROOM_TOP_RIGHT,
    ROOM_RIGHT_BOT,
    ROOM_BOT_LEFT,
    ROOM_LEFT_TOP_RIGHT,
    ROOM_LEFT_TOP_RIGHT_2,
    ROOM_LEFT_TOP_RIGHT_3,
    ROOM_LEFT_TOP_RIGHT_4,
    ROOM_TOP_RIGHT_BOT,
    ROOM_TOP_RIGHT_BOT_2,
    ROOM_TOP_RIGHT_BOT_3,
    ROOM_TOP_RIGHT_BOT_4,
    ROOM_RIGHT_BOT_LEFT,
    ROOM_RIGHT_BOT_LEFT_2,
    ROOM_RIGHT_BOT_LEFT_3,
    ROOM_RIGHT_BOT_LEFT_4,
    ROOM_BOT_LEFT_TOP,
    ROOM_BOT_LEFT_TOP_2,
    ROOM_BOT_LEFT_TOP_3,
    ROOM_BOT_LEFT_TOP_4,
    NO_ROOM,
    ROOM_ALL,
    ONE_DOOR_START = ROOM_LEFT,
    ONE_DOOR_END = ROOM_BOT,
    TWO_DOOR_START = ROOM_LEFT_RIGHT,
    TWO_DOOR_END = ROOM_BOT_LEFT,
    THREE_DOOR_START = ROOM_LEFT_TOP_RIGHT,
    THREE_DOOR_END = ROOM_BOT_LEFT_TOP_3
} room_t;

static const room_t left_door[] = {
    ROOM_LEFT,
    ROOM_LEFT_RIGHT,
    ROOM_LEFT_TOP,
    ROOM_BOT_LEFT,
    ROOM_LEFT_TOP_RIGHT,
    ROOM_RIGHT_BOT_LEFT,
    ROOM_BOT_LEFT_TOP,
    ROOM_LEFT_TOP_RIGHT_2,
    ROOM_RIGHT_BOT_LEFT_2,
    ROOM_BOT_LEFT_TOP_2,
    ROOM_LEFT_TOP_RIGHT_3,
    ROOM_RIGHT_BOT_LEFT_3,
    ROOM_BOT_LEFT_TOP_3,
    ROOM_LEFT_TOP_RIGHT_4,
    ROOM_RIGHT_BOT_LEFT_4,
    ROOM_BOT_LEFT_TOP_4,
    ROOM_ALL
};

static const room_t top_door[] = {
    ROOM_TOP,
    ROOM_TOP_BOT,
    ROOM_TOP_RIGHT,
    ROOM_LEFT_TOP,
    ROOM_LEFT_TOP_RIGHT,
    ROOM_TOP_RIGHT_BOT,
    ROOM_BOT_LEFT_TOP,
    ROOM_LEFT_TOP_RIGHT_2,
    ROOM_TOP_RIGHT_BOT_2,
    ROOM_BOT_LEFT_TOP_2,
    ROOM_LEFT_TOP_RIGHT_3,
    ROOM_TOP_RIGHT_BOT_3,
    ROOM_BOT_LEFT_TOP_3,
    ROOM_LEFT_TOP_RIGHT_4,
    ROOM_TOP_RIGHT_BOT_4,
    ROOM_BOT_LEFT_TOP_4,
    ROOM_ALL
};

static const room_t right_door[] = {
    ROOM_RIGHT,
    ROOM_LEFT_RIGHT,
    ROOM_TOP_RIGHT,
    ROOM_RIGHT_BOT,
    ROOM_LEFT_TOP_RIGHT,
    ROOM_TOP_RIGHT_BOT,
    ROOM_RIGHT_BOT_LEFT,
    ROOM_LEFT_TOP_RIGHT_2,
    ROOM_TOP_RIGHT_BOT_2,
    ROOM_RIGHT_BOT_LEFT_2,
    ROOM_LEFT_TOP_RIGHT_3,
    ROOM_TOP_RIGHT_BOT_3,
    ROOM_RIGHT_BOT_LEFT_3,
    ROOM_LEFT_TOP_RIGHT_4,
    ROOM_TOP_RIGHT_BOT_4,
    ROOM_RIGHT_BOT_LEFT_4,
    ROOM_ALL
};

static const room_t bot_door[] = {
    ROOM_BOT,
    ROOM_TOP_BOT,
    ROOM_RIGHT_BOT,
    ROOM_BOT_LEFT,
    ROOM_TOP_RIGHT_BOT,
    ROOM_RIGHT_BOT_LEFT,
    ROOM_BOT_LEFT_TOP,
    ROOM_TOP_RIGHT_BOT_2,
    ROOM_RIGHT_BOT_LEFT_2,
    ROOM_BOT_LEFT_TOP_2,
    ROOM_TOP_RIGHT_BOT_3,
    ROOM_RIGHT_BOT_LEFT_3,
    ROOM_BOT_LEFT_TOP_3,
    ROOM_TOP_RIGHT_BOT_4,
    ROOM_RIGHT_BOT_LEFT_4,
    ROOM_BOT_LEFT_TOP_4,
    ROOM_ALL
};

//Functions to use

void set_empty_map(room_t rooms[21][21]);
room_t get_room(status_t status[4], room_t start, room_t end);
bool make_a_good_move(room_t rooms[21][21], size_t *x, size_t *y, int nb);
bool make_a_bad_move(room_t rooms[21][21], size_t *x, size_t *y, int nb);
int get_random_nb(int n, int m);
bool is_good_room(room_t room, const room_t directions[], status_t status);

void generate_room(room_t rooms[21][21]);

#endif /* !CREATION_H_ */
