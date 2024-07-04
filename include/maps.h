/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** maps.h
*/

#include "entity.h"

#ifndef MAPS_H_
    #define MAPS_H_

    #include "sprites.h"
    #include "my.h"
    #include <SFML/Graphics.h>

//////////////// STATICS MAP READ ////////////////

//Map display utils
    #define MAP_SQUARE 100
    #define MAP_VISIBLE_X 1920
    #define MAP_VISIBLE_Y 1080

    #define ASSET_MAP_SIZE 50

//Reading map char
    #define MAP_PNJ 'P'
    #define MAP_CHEST 'C'
    #define MAP_MONSTER 'M'
    #define MAP_BOSS 'B'
    #define MAP_DOOR 'D'
    #define MAP_WALL 'X'
    #define MAP_FLOOR ' '
    #define MAP_HEAL 'H'
    #define SIZE_MAP 20
    #define MOVE_EXPLO_ANIM (double)1/6

//Map assets animation
    #define MAP_ASSET_ANIMATION_SPEED 0.3

//Mapping inside the dungeon
    #define ACTUAL_MAP dungeon->maps[dungeon->co_map.y][dungeon->co_map.x]
    #define SIZE_DUNGEON 21
    #define BOSS_TO_WIN 1

typedef enum much_doors_e {
    L_T_R = 10,
    T_R_B,
    R_B_L,
    B_L_T,
    ALL
} much_doors_t;


static char *MAPS_FILEPATH[] = {
    "assets/battle_maps/one_door/map_door_left.txt",
    "assets/battle_maps/one_door/map_door_top.txt",
    "assets/battle_maps/one_door/map_door_right.txt",
    "assets/battle_maps/one_door/map_door_bot.txt",
    "assets/battle_maps/two_door/map_door_left_right.txt",
    "assets/battle_maps/two_door/map_door_top_bot.txt",
    "assets/battle_maps/two_door/map_door_left_top.txt",
    "assets/battle_maps/two_door/map_door_top_right.txt",
    "assets/battle_maps/two_door/map_door_right_bot.txt",
    "assets/battle_maps/two_door/map_door_bot_left.txt",
    "assets/battle_maps/three_door/map_door_left_top_right.txt",
    "assets/battle_maps/three_door/map_door_top_right_bot.txt",
    "assets/battle_maps/three_door/map_door_right_bot_left.txt",
    "assets/battle_maps/three_door/map_door_bot_left_top.txt",
    "assets/battle_maps/four_door/map_door_all.txt",
    "files/tutos/map.txt"
};

static char *BOSS_FILEPATH[] = {
    "assets/battle_maps/boss/boss_left.txt",
    "assets/battle_maps/boss/boss_up.txt",
    "assets/battle_maps/boss/boss_right.txt",
    "assets/battle_maps/boss/boss_down.txt",
    "",
    "",
    "assets/battle_maps/boss/boss_left_up.txt",
    "assets/battle_maps/boss/boss_up_right.txt",
    "assets/battle_maps/boss/boss_right_down.txt",
    "assets/battle_maps/boss/boss_down_left.txt"
};

//Number of maps
static const int NB_MAPS = sizeof(MAPS_FILEPATH) / sizeof(char *);

//////////////// STATICS BACKGROUND ////////////////

//Assets display
enum bg_assets {
    EMPTY,
    ROCK_GROUND_1,
    ROCK_GROUND_2,
    ROCK_GROUND_3,
    WALL_LEFT,
    WALL_RIGHT,
    WALL_TOP_LEFT,
    WALL_TOP_RIGHT,
    WALL_BOTTOM_LEFT,
    WALL_BOTTOM_RIGHT,
    WALL_BOTTOM,
    WALL,
    CHEST,
    MONSTER,
    PNJ,
    FOUNTAIN ,
    DOOR_LEFT,
    DOOR_TOP,
    DOOR_BOT,
    DOOR_RIGHT
};

static char *BG_FILEPATH_ASSETS[] = {
    "assets/battle_maps/background/empty.png",
    "assets/battle_maps/background/ground1.png",
    "assets/battle_maps/background/ground2.png",
    "assets/battle_maps/background/ground3.png",
    "assets/battle_maps/background/wall_left.png",
    "assets/battle_maps/background/wall_right.jpg",
    "assets/battle_maps/background/wall_top_left.png",
    "assets/battle_maps/background/wall_top_right.jpg",
    "assets/battle_maps/background/wall_bottom_left.jpg",
    "assets/battle_maps/background/wall_bottom_right.jpg",
    "assets/battle_maps/background/wall_bottom.jpg",
    "assets/battle_maps/background/wall.png",
    "assets/battle_maps/background/chest.png",
    "assets/battle_maps/background/monster_Idle.png",
    "assets/characters/pnj_idle_left.png",
    "assets/combat/icons/Spells/divine_protection_spell.png",
    "assets/battle_maps/background/door_left.png",
    "assets/battle_maps/background/top_door.png",
    "assets/battle_maps/background/bottom_door.png",
    "assets/battle_maps/background/right_door.png",
};

static sfVector2f BG_SIZE_ASSETS[] = {
    {50, 50}, // EMPTY
    {50, 50}, // GROUNDS
    {50, 50},
    {50, 50},
    {50, 50}, // WALLS
    {50, 50},
    {50, 50},
    {50, 50},
    {50, 50},
    {50, 50},
    {50, 50},
    {50, 50},
    {40, 50}, // CHEST
    {32, 32}, // MONSTER
    {32, 32}, // PNJ
    {16, 16}, // FOUNTAIN
    {64, 80}, // DOORS
    {64, 68},
    {64, 68},
    {64, 80},
};

//////////////// STRUCTURE ////////////////

typedef struct maps_s {
    sfVector2i co_map;
    char **char_map;
} maps_t;

typedef struct map_display_s {
    int index;
    int number;
    sprite_t *display;
    sfVector2f *pos;
    sfIntRect *rect;
} map_display_t;

typedef struct dungeon_s {
    size_t floor;
    sprite_t background;
    my_clock_t *clock;
    map_display_t monster;
    map_display_t interaction;
    map_display_t pnj;
    map_display_t assets;
    sfVector2i co_map;
    maps_t maps[SIZE_DUNGEON][SIZE_DUNGEON];
    pnj_t **pnjs;
} dungeon_t;

//////////////// FUNCTION ////////////////

/* MAP MANAGEMENT */
void get_sprite_map(dungeon_t *dungeon, entity_t *player);
void setup_map_assets(dungeon_t *dungeon, char **map);
void move_map(dungeon_t *dungeon, double x, double y);
void change_map(dungeon_t *dungeon, entity_t *player);
void destroy_map_display(dungeon_t *dungeon);

/* SETTING UP */
char **get_boss_file(int map_enum);
char **get_map_from_file(int map_enum);
dungeon_t *setup_dungeon(entity_t *player);
maps_t **setup_empty_links(void);
int setup_links_map(maps_t **maps);

#endif
