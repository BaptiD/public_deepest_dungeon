/*
** EPITECH PROJECT, 2024
** B-MUL-200-PAR-2-1-myrpg-pierre.pruvost
** File description:
** setup_dungeon.c
*/

#include <stddef.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <math.h>
#include <stdio.h>

#include "creation.h"
#include "my.h"
#include "maps.h"
#include "statics.h"
#include "entity.h"

static void three_doors_mess(maps_t *map, room_t room)
{
    int number = 0;

    if (room >= ROOM_LEFT_TOP_RIGHT && room <= ROOM_LEFT_TOP_RIGHT_4)
        number = L_T_R;
    if (room >= ROOM_TOP_RIGHT_BOT && room <= ROOM_TOP_RIGHT_BOT_4)
        number = T_R_B;
    if (room >= ROOM_RIGHT_BOT_LEFT && room <= ROOM_RIGHT_BOT_LEFT_4)
        number = R_B_L;
    if (room >= ROOM_BOT_LEFT_TOP && room <= ROOM_BOT_LEFT_TOP_4)
        number = B_L_T;
    if (room == ROOM_ALL)
        number = ALL;
    map->char_map = get_map_from_file(number);
}

static maps_t get_map_from_room(room_t room, int x, int y)
{
    maps_t map;

    map.co_map = (sfVector2i){x, y};
    map.char_map = NULL;
    if (room == NO_ROOM)
        return map;
    if (room <= TWO_DOOR_END) {
        map.char_map = get_map_from_file(room);
    } else
        three_doors_mess(&map, room);
    return map;
}

static void get_another_boss(sfVector2i *far, sfVector2i *cmp,
    room_t rooms[21][21])
{
    cmp->x = 0;
    cmp->y = 0;
    while (cmp->y < 21) {
        if (rooms[cmp->y][cmp->x] >= ROOM_LEFT_TOP
        && rooms[cmp->y][cmp->x] <= TWO_DOOR_END &&
        sqrt(pow(10 - cmp->x, 2) + pow(10 - cmp->y, 2)) >=
        sqrt(pow(10 - far->x, 2) + pow(10 - far->y, 2))) {
            far->x = cmp->x;
            far->y = cmp->y;
        }
        cmp->x++;
        if (cmp->x >= 21) {
            cmp->x = 0;
            cmp->y++;
        }
    }
}

static void get_dungeon_boss(dungeon_t *dungeon, room_t rooms[21][21])
{
    sfBool found = sfFalse;
    sfVector2i far = {10, 10};
    sfVector2i cmp = {0, 0};

    while (cmp.y < 21) {
        if (rooms[cmp.y][cmp.x] >= ONE_DOOR_START
        && rooms[cmp.y][cmp.x] <= ONE_DOOR_END &&
        sqrt(pow(10 - cmp.x, 2) + pow(10 - cmp.y, 2)) >=
        sqrt(pow(10 - far.x, 2) + pow(10 - far.y, 2))) {
            far.x = cmp.x;
            far.y = cmp.y;
        }
        cmp.x++;
        if (cmp.x >= 21) {
            cmp.x = 0;
            cmp.y++;
        }
    }
    if (far.x == 10 && far.y == 10)
        get_another_boss(&far, &cmp, rooms);
    dungeon->maps[far.y][far.x].char_map = get_boss_file(rooms[far.y][far.x]);
}

static int setup_maps(dungeon_t *dungeon)
{
    room_t rooms[SIZE_DUNGEON][SIZE_DUNGEON];

    generate_room(rooms);
    logs(INFO, "Setting up maps...");
    for (int y = 0; y < SIZE_DUNGEON; y++) {
        for (int x = 0; x < SIZE_DUNGEON; x++) {
            dungeon->maps[y][x] = get_map_from_room(rooms[y][x], x, y);
        }
    }
    get_dungeon_boss(dungeon, rooms);
    logs(SUCCESS, "Setting up maps OK");
    return SUCCESS;
}

dungeon_t *setup_dungeon(entity_t *player)
{
    dungeon_t *dungeon = NULL;

    logs(INFO, "Setting up dungeon...");
    dungeon = malloc(sizeof(dungeon_t));
    if (dungeon == NULL) {
        logs(ERROR, "Malloc failed");
        return NULL;
    }
    dungeon->floor = 0;
    dungeon->co_map = (sfVector2i){10, 10};
    if (setup_maps(dungeon) == ERROR)
        return NULL;
    dungeon->pnjs = setup_pnjs(player);
    dungeon->clock = set_clock();
    logs(SUCCESS, "Setting up dungeon OK");
    return dungeon;
}
