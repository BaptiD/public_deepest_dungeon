/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** statics.h
*/

#ifndef MENUS_H_
    #define MENUS_H_
    #include <SFML/Graphics.h>

    #define UNSELECTED -1
    #define OUT 0
    #define IN 1

    #define NB_HEROES 3

static const sfVector2f SELECTOR_POS = {0, 250};
static const sfVector2f SELECTOR_OFST = {640, 0};

    #define HERO_HEIGHT 700

enum menus_sprites {
    HEROES_BCKG = 0,
    SELECT = 1,
    IDLE_FIRE_KNIGHT = 2,
    IDLE_WIZARD_WANDERER = 3,
    IDLE_NINJA_PEASANT = 4,
    START_GAME = 5,
    QUIT_GAME = 6,
    LOBBY_BCKG = 7,
    LOAD_SAVE = 8,
    BACK = 9,
    IG_MENU_BCKG = 10,
    HELP = 11,
    OPTIONS = 12,
    RED_CROSS = 13,
    HELP_POP = 14,
    MAIN_MENU = 15,
    OPTIONS_BG = 16,
    SPEAKER_ON = 17,
    SPEAKER_OFF = 18,
    DRAG_BALL = 19,
};

//Images paths
static const char *MENU_IMG_PATH[] = {
    "assets/menus/heroes/back_selection.png",
    "assets/menus/heroes/select.png",
    "assets/characters/combat_sprites/fire_knight/Idle.png",
    "assets/characters/combat_sprites/wizard_wanderer/Idle.png",
    "assets/characters/combat_sprites/ninja_peasant/Idle.png",
    "assets/menus/lobby/play.png",
    "assets/menus/lobby/quit.png",
    "assets/menus/lobby/background.png",
    "assets/menus/lobby/load.png",
    "assets/menus/in_game/back.png",
    "assets/menus/in_game/background.png",
    "assets/menus/in_game/help.png",
    "assets/menus/in_game/options.png",
    "assets/menus/in_game/cross.png",
    "assets/menus/in_game/help_pop.png",
    "assets/menus/in_game/main_menu.png",
    "assets/menus/options/background.png",
    "assets/menus/options/speaker_on.png",
    "assets/menus/options/speaker_off.png",
    "assets/menus/options/ball.png"
};

static const int NB_MENU_IMG = sizeof(MENU_IMG_PATH) / sizeof(char *);

static const sfVector2f LOAD_BAR_POS = {640, 670};
static const sfVector2f RESIZE_LOAD_BORDER = {10, 10};
static const sfVector2f LOAD_BORDER_ORIGIN = {4.5, 32};
static const sfVector2f LOAD_BAR_SIZES[] = {
    {0.1, 1},
    {0.7, 1},
    {0.9, 1},
    {1, 1}
};
static const sfVector2f LOAD_BAR_OFST = {29, 26};

static const sfIntRect FIRST_RECT[] = {
    {0},
    {0},
    {0, 0, 96, 96},
    {0, 0, 128, 128},
    {0, 0, 96, 96},
    {0, 0, 550, 118},
    {0, 0, 440, 95},
    {0},
    {0, 0, 440, 95},
    {0, 0, 440, 95},
    {0},
    {0, 0, 440, 95},
    {0, 0, 440, 95},
    {0, 0, 50, 50},
    {0},
    {0, 0, 440, 95},
    {0},
    {0, 0, 70, 70},
    {0, 0, 70, 70},
    {0, 0, 39, 39}
};

//Image real size
//fill with real .png/.jpg image size {x, y}
static const sfVector2f MENU_IMG_SIZE[] = {
    {1920, 1080},
    {392, 62},
    {768, 96},
    {1024, 128},
    {576, 96},
    {550, 118},
    {440, 95},
    {1920, 1080},
    {440, 95},
    {440, 95},
    {1920, 1080},
    {440, 95},
    {440, 95},
    {50, 50},
    {1920, 1080},
    {440, 95},
    {1920, 1080},
    {70, 70},
    {70, 70},
    {39, 39}
};

//Image desired size
//fill with the targeted size you want for the sprite {x, y}
static const sfVector2f MENU_IMG_RESIZE[] = {
    {1920, 1080},
    {392, 62},
    {768 * 4, 96 * 4},
    {1024 * 4, 128 * 4},
    {576 * 4, 96 * 4},
    {550, 118},
    {440, 95},
    {1920, 1080},
    {440, 95},
    {440, 95},
    {1920, 1080},
    {440, 95},
    {440, 95},
    {50, 50},
    {1920, 1080},
    {440, 95},
    {1920, 1080},
    {70, 70},
    {70, 70},
    {39, 39}
};

//sprite position
static const sfVector2f MENU_IMG_POSITION[] = {
    {0, 0},
    {-1000, -1000},
    {130, 750},
    {730, 750},
    {1410, 750},
    {685, 343},
    {740, 830},
    {0, 0},
    {740, 484},
    {740, 370},
    {0, 0},
    {740, 715},
    {740, 600},
    {1765, 90},
    {0, 0},
    {740, 484},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
};

#endif
