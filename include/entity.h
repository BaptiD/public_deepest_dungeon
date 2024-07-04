/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** player.h
*/

#ifndef PLAYER_H_
    #define PLAYER_H_

    #include "sprites.h"
    #include <unistd.h>
    #include <stdlib.h>
    #include <stdbool.h>
    #include <SFML/Graphics.h>

//Sprite for entitys
    #define EXPLO_STATE 0
    #define COMBAT_STATE 1
    #define DIALOGUE 0
    #define NAME 1
    #define LEFT 0
    #define RIGHT 1
    #define UP 2
    #define DOWN 3
    #define IDLE_EXPLO 2
    #define ID_RUN_RIGHT 0
    #define ID_RUN_LEFT 3
    #define ID_IDLE_RIGHT 6
    #define ID_IDLE_LEFT 9
    #define NB_PNJ 10
    #define DONE 0
    #define NOT_DONE 1
    #define ID_PNJ_SPRITE 12
    #define DIALOGUE_SQUAD_FULL "Oh ! Your team is full... Come back later !"

    #define XP_TO_LVL_UP 40
    #define RATIO_XP_LVL_UP 1.2
    #define RATIO_XP_MONSTER_KILL 0.5

    #define MONSTER_ENTITY 666
    #define ALLY_ENTITY 0

    #define COMBAT_SPRITE_SIZE 384.0

enum entity {
    FIRE_KNIGHT = 0,
    WIZARD_WANDERER = 1,
    NINJA_PEASANT = 2,
    SAMURAI = 3,
    FIRE_WIZARD = 4,
    LIGHTNING_MAGE = 5,
    SAMURAI_ARCHER = 6,
    SAMURAI_COMMANDER = 7,
    NINJA_MONK = 8,
    KUNOICHI = 9,
    SQ_WARRIOR = 10,
    SQ_SPEAR = 11,
    SQ_ARC = 12,
    KARASU = 13,
};

// Possible position for monster
static const int MONSTER_POS[][4] = {
    {0, 0, 1, 1},
    {0, 1, 1, 1},
    {1, 1, 0, 0}
};

static char *ENTITY_INFO_FILEPATH[] = {
    "assets/characters/fire_knight.txt",
    "assets/characters/wizard_wanderer.txt",
    "assets/characters/ninja_peasant.txt",
    "assets/characters/samurai.txt",
    "assets/characters/fire_wizard.txt",
    "assets/characters/lightning_mage.txt",
    "assets/characters/samurai_archer.txt",
    "assets/characters/samurai_commander.txt",
    "assets/characters/ninja_monk.txt",
    "assets/characters/kunoichi.txt",
    "assets/characters/sq_warrior.txt",
    "assets/characters/sq_spear.txt",
    "assets/characters/sq_arc.txt",
    "assets/characters/karasu_tengu.txt",
};

static char *ENTITY_EXPLO_SPRITE_FILEPATH[] = {
    "assets/Heroes/Knight/knight-run-right.png",
    "assets/Heroes/Wizzard/Run/wizzard-run-right.png",
    "assets/Heroes/Rogue/Run/rogue-run-right.png",
    "assets/Heroes/Knight/knight-run-left.png",
    "assets/Heroes/Wizzard/Run/wizzard-run-left.png",
    "assets/Heroes/Rogue/Run/rogue-run-left.png",
    "assets/Heroes/Knight/knight-idle-right.png",
    "assets/Heroes/Wizzard/Idle/wizzard-idle-right.png",
    "assets/Heroes/Rogue/Idle/rogue-idle-right.png",
    "assets/Heroes/Knight/knight-idle-left.png",
    "assets/Heroes/Wizzard/Idle/wizzard-idle-left.png",
    "assets/Heroes/Rogue/Idle/rogue-idle-left.png",
    "assets/characters/pnj_idle_left.png",
    "assets/characters/pnj_idle_left.png",
    "assets/characters/pnj_idle_left.png",
    "assets/characters/pnj_idle_left.png",
    "assets/characters/pnj_idle_left.png",
    "assets/characters/pnj_idle_left.png",
    "assets/characters/pnj_idle_left.png",
    "assets/characters/pnj_idle_left.png",
};

static char *PNJS_FILE[] = {
    "files/pnjs/fire_knight.txt",
    "files/pnjs/wizard_wanderer.txt",
    "files/pnjs/ninja_peasant.txt",
    "files/pnjs/samurai.txt",
    "files/pnjs/fire_wizard.txt",
    "files/pnjs/lightning_mage.txt",
    "files/pnjs/samurai_archer.txt",
    "files/pnjs/samurai_commander.txt",
    "files/pnjs/ninja_monk.txt",
    "files/pnjs/kunoichi.txt",
    "files/tutos/pnj.txt"
};

// Reading file for setting up
    #define NAME_ENT "##name"
    #define STATS_ENT "##stats"
    #define CAPA_ENT "##capacity"
    #define XP_ENT "##experience"

///////// STATS /////////

    #define NB_STATS 6

    #define UP_ATK 1
    #define UP_HP 5
    #define UP_SPD 1
    #define UP_CRT 1
    #define UP_PRE 2

enum stats_enum {
    ATK,
    HP,
    SPD,
    CRT,
    PRE,
    PRO
};

typedef struct stats_s {
    int atk;    /*Attack*/
    int hp;     /*Health*/
    int spd;    /*Speed*/
    int crt;    /*Critical chance*/
    int pre;    /*Precision*/
    int pro;    /*Protection*/
} stats_t;

///////// EFFECTS /////////

    #define SIZE_EFFECT_WANTED 150
    #define POS_EFFECT_Y 230
    #define MONSTER_POS_EFFECT_X -240
    #define ALLY_POS_EFFECT_X 130

enum every_effects {
    STUN_EFFECT,
    BLEED_EFFECT,
    BURN_EFFECT,
    POISON_EFFECT,
};

static char *EFFECT_FILEPATH[] = {
    "assets/combat/effects/stun.png",
    "assets/combat/effects/bleed.png",
    "assets/combat/effects/burn.png",
    "assets/combat/effects/poison.png",
};

static int SIZEOF_EFFECT[] = {
    32,
    150,
    32,
    32,
};

static sfVector2i NB_IMAGES_EFFECT[] = {
    {6, 2},
    {5, 6},
    {6, 2},
    {6, 2},
};

enum effects_struct {
    NB_TURN_EFFECT = 0,
    DAMAGES_EFFECT = 1,
};

typedef struct effects_s {
    int stun[2];
    int bleed[2];
    int burn[2];
    int poison[2];
} effects_t;

///////// EQUIPEMENT /////////

    #define INVENTORY_SIZE 12
    #define NB_ITEMS_SQUAD 3
    #define NB_ENTITY_SQUAD 4

///////// ENTITY /////////

typedef struct text_s {
    sfText *text;
    char *dialogue;
    sprite_t *sprite;
} text_t;

typedef struct pnj_s {
    char *name;
    int id;
    sfVector2i co_room;
    int type;
    bool is_talking;
    int status_quest;
    char **dialogue;
    int dialogue_line;
    text_t *text[2];
    sprite_t *display[2];
    sfIntRect rect;
    int pos[2];
    sfClock *clock;
} pnj_t;

/* Structure for the entity */
typedef struct entity_s {
    int id;                         /* Index and ID of the entity */
    sprite_t *display[2];           /* Displays [0]-Explo [1]-Combat */
    sfIntRect rect;                 /* Display rect for sprite */
    int status;                     /* Status of the entity (Combat) */
    int pos[2];                     /* Position in the dungeon */
    char name[128];                 /* Name of the entity */
    int level;                      /* Level of the entity */
    int xp;                         /* Experience to level up */
    stats_t *stats;                 /* Base stats (Combat) */
    stats_t *mod;                   /* Modification stats (Combat) */
    effects_t effects;              /* Effect that impact the entity */
    int capacities[4];              /* Index of every capacities */
    int inventory[INVENTORY_SIZE];  /* Inventory of the entity */
    int items[3];                   /* Active Item of the entity */
    struct entity_s **squad;        /* Squad of the entity */
    int orientation;                /* Orientation of the entity (Explo) */
    int movement;                   /* Movement of the entity (Explo) */
    sfClock *clock;                 /* Clock for the animation */
} entity_t;

    #include "maps.h"

///////// FUNCTIONS /////////

/* Setting up */
entity_t *setting_entity_from_file(int entity_enum);
void set_entity_sprite_combat(entity_t *entity, int entity_enum);
void set_entity_sprite_explo(entity_t *entity, int entity_enum);
stats_t *set_stats(char *line);
stats_t *set_mod_empty(void);
effects_t set_empty_effects(void);

/* Manage */
void swap_entity(entity_t *player, int index_1, int index_2);

/* Clear */
void destroy_entities(entity_t *entity);

/* PNJS */
void add_pnj(pnj_t **pnj, int i, int player_id);
void pars_pnj_file(pnj_t *pnj, int type);
pnj_t **setup_pnjs(entity_t *player);
int squad_size(entity_t *player);
entity_t *transform_pnj_to_entity(pnj_t *pnj);
void add_pnj_to_squad(entity_t *player, pnj_t *pnj);
void add_entity_to_squad(entity_t *entity_squad, entity_t *new_entity,
    int pose);

/* Utils Pnjs */
bool is_close_to_pnj(pnj_t *pnj, entity_t *play);
void set_pnj_in_map(maps_t *map, pnj_t **pnjs, entity_t *player);

/* Display */
sfIntRect display_entity(sfRenderWindow *window, sfClock *clock,
    sprite_t *display, sfIntRect rect);


#endif
