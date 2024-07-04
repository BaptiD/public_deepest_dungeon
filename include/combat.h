/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** combat.h
*/

#ifndef COMBAT_H_
    #define COMBAT_H_
    #include "game.h"
    #include "items.h"

//////////////// STATICS ////////////////

// Background
    #define COMBAT_BG "assets/combat/background.jpg"
static sfVector2f COMBAT_BG_POS = {0, -93};

/*      POSITION ASSETS     */

// Entity pos in field
    #define ENTITY_POS_Y 348
    #define ENTITY_DISTANCE (COMBAT_SPRITE_SIZE / 2)
    #define MONSTER_POS_X 952

// HP bar pos
    #define HP_BAR_POS_Y 572
    #define HP_BAR_RATIO 2.5
    #define HP_BAR_MONSTER_X -95
    #define HP_BAR_ALLY_X 95

// Lvl pos
    #define LVL_POS_Y 545
    #define LVL_MONSTER_X (HP_BAR_MONSTER_X + 5)
    #define LVL_ALLY_X (HP_BAR_ALLY_X + 5)

// Entity turn indicator
    #define TURN_INDICATOR_Y (ENTITY_POS_Y + 140)
    #define ALLY_TURN_INDICATOR_X 130
    #define MONSTER_TURN_INDICATOR_X -230

// Focus indicator
    #define FOCUS_INDICATOR_Y (ENTITY_POS_Y + COMBAT_SPRITE_SIZE)
    #define ALLY_FOCUS_INDI_X 130
    #define MONSTER_FOCUS_INDI_X -230

// Hit and XP indicator
    #define HIT_INDICATOR_Y (ENTITY_POS_Y + 160)
    #define ALLY_HIT_INDI_X 120
    #define MONSTER_HIT_INDI_X -140

// Capacity description
static const sfVector2f POS_DESCRIPTION_COMBAT = {990, 850};

/*                          */

// Animation clock
    #define CLOCK_RESTART 5.0
    #define ANIMATION_SPEED 0.12

// Played status
    #define PLAYED 1
    #define WAIT 0

// Animation continue or stop
    #define STOP 1
    #define CONTINUE 0

////////// POSITION UI //////////

static const sfVector2f STATS_POS_COMBAT[] = {
    {50, 850},
    {50, 900},
    {50, 950},
    {250, 850},
    {250, 900},
    {250, 950},
};

    #define DEAD_SCREEN_START (sfVector2f){0, -1080}

// Information combat stats
    #define CRIT_RATIO 1.5
    #define PROT_RATIO 0.1
    #define IGNORE -42

// Capacity type
enum capa_type {
    MISS,
    BASIC,
    CRIT,
    HEAL,
    HEAL_CRIT,
    STAT_UP,
    STAT_DOWN,
    ATK_UP,
    ATK_DOWN,
    SPD_UP,
    SPD_DOWN,
    PRO_UP,
    PRO_DOWN,
    CRT_UP,
    CRT_DONW,
    PRE_UP,
    PRE_DOWN,
};

// Boss
enum boss_list {
    NO_BOSS = -1,
    BOSS_KARASU = 1,
};

//////////////// STRUCTURE ////////////////

typedef struct combat_s {
    sprite_t background;
    entity_t **field;
    int index_clock;
    sfClock *clock;
    int capa_pressed;
    int turn;
    int *played;
} combat_t;

typedef struct cap_info_s {
    int entity_hit[NB_ENTITY_SQUAD * 2];
    int type[NB_ENTITY_SQUAD * 2];
} cap_info_t;

//////////////// FUNCTION ////////////////

/* Main loop */
void combat_arrival(combat_t *info, display_t *display);
void combat_loop(display_t *display, entity_t *player, int boss,
    int *run_game);
void clock_restart(combat_t *info);
void clear_combat(combat_t *info, int player_id);

/* Events */
void combat_event_manager(display_t *display, combat_t *info, int *run_game,
    int *run_combat);
sfBool position_capa(combat_t *info, entity_t *entity, int key);
sfBool can_focus(combat_t *info, int focus);
void capacity_event(display_t *display, combat_t *info, int key,
    int focus);
void monster_capacity_event(display_t *display, combat_t *info);
void next_turn(display_t *display, combat_t *info);

/* Set up */
combat_t *set_combat(entity_t *player, entity_t *monster);
entity_t *set_monster_squad(entity_t *player, int boss);

/* Effect management */
void effect_manage(display_t *display, combat_t *info);
void do_effect_by_type(combat_t *info, int effect);
void bleed_entity(entity_t *entity, int chance, int damages, int turn);
void burn_entity(entity_t *entity, int chance, int damages, int turn);
void poison_entity(entity_t *entity, int chance, int damages, int turn);
void stun_entity(entity_t *entity, int chance);

/* Display */
void draw_filed_entity(sfRenderWindow *window, combat_t *info);
void draw_combat(display_t *display, combat_t *info);
void draw_turn_entity(display_t *display, combat_t *info);
void display_damage_hit(display_t *display, combat_t *info,
    cap_info_t *cap);
void display_health_bar(sfRenderWindow *window, sprite_t *sprites,
    combat_t *info);
void display_xp_combat(display_t *display, combat_t *info, int xp_gain,
    int i);
void display_lvl_combat(display_t *display, combat_t *info);
void display_stats_combat(display_t *display, combat_t *info);
void display_capacities_combat(display_t *display, combat_t *info);

/* Animation */
void anim_idle_field(combat_t *info);
sfBool is_impact_frame(combat_t *info, cap_info_t *cap);
void hit_animation(combat_t *info, int focus);

/* Combat Info */
sfBool is_alive(entity_t *entity);
void change_sprite_action(entity_t *entity, int action);
sfBool is_combat_start(dungeon_t *dungeon, entity_t *player);
sfBool is_combat_finished(combat_t *info, entity_t *player,
    display_t *display);

/* Xp */
void display_xp_gain(combat_t *info, display_t *display);

//////////////// ANIMATION ////////////////

    #define NB_ANIMATION_ENTITY 7

//Combat animation
enum combat_anim {
    IDLE,
    DEAD,
    HURT,
    CAPA_1,
    CAPA_2,
    CAPA_3,
    CAPA_4,
};

typedef struct animation_s {
    char *path;
    int nb_anim;
    int x_max;
    int y_max;
    int frame_x;
    int impact_frame;
} animation_t;


static animation_t COMBAT_ANIMATION[14][NB_ANIMATION_ENTITY] = {
    {
        {"assets/characters/combat_sprites/fire_knight/Idle.png",
            8, 768, 96, 96, 1},
        {"assets/characters/combat_sprites/fire_knight/Dead.png",
            10, 960, 96, 96, 1},
        {"assets/characters/combat_sprites/fire_knight/Hurt.png",
            5, 480, 96, 96, 1},
        {"assets/characters/combat_sprites/fire_knight/Attack_1.png",
            10, 960, 96, 96, 5},
        {"assets/characters/combat_sprites/fire_knight/Attack_2.png",
            6, 480, 96, 96, 4},
        {"assets/characters/combat_sprites/fire_knight/Block.png",
            8, 768, 96, 96, 5},
        {"assets/characters/combat_sprites/fire_knight/Attack_3.png",
            17, 1632, 96, 96, 13},
    },
    {
        {"assets/characters/combat_sprites/wizard_wanderer/Idle.png",
            8, 1024, 128, 128, 1},
        {"assets/characters/combat_sprites/wizard_wanderer/Dead.png",
            4, 512, 128, 128, 1},
        {"assets/characters/combat_sprites/wizard_wanderer/Hurt.png",
            4, 512, 128, 128, 1},
        {"assets/characters/combat_sprites/wizard_wanderer/Magic_arrow.png",
            6, 768, 128, 128, 1},
        {"assets/characters/combat_sprites/wizard_wanderer/Attack_1.png",
            7, 896, 128, 128, 1},
        {"assets/characters/combat_sprites/wizard_wanderer/Attack_2.png",
            9, 1152, 128, 128, 1},
        {"assets/characters/combat_sprites/wizard_wanderer/Magic_sphere.png",
            16, 2048, 128, 128, 1},
    },
    {
        {"assets/characters/combat_sprites/ninja_peasant/Idle.png",
            6, 576, 96, 96, 1},
        {"assets/characters/combat_sprites/ninja_peasant/Dead.png",
            4, 384, 96, 96, 1},
        {"assets/characters/combat_sprites/ninja_peasant/Hurt.png",
            2, 192, 96, 96, 1},
        {"assets/characters/combat_sprites/ninja_peasant/Attack_1.png",
            6, 576, 96, 96, 1},
        {"assets/characters/combat_sprites/ninja_peasant/Attack_2.png",
            4, 384, 96, 96, 1},
        {"assets/characters/combat_sprites/ninja_peasant/Disguise.png",
            9, 864, 96, 96, 1},
        {"assets/characters/combat_sprites/ninja_peasant/Shot.png",
            6, 576, 96, 96, 1},
    },
    {
        {"assets/characters/combat_sprites/samurai/Idle.png",
            6, 768, 128, 128, 1},
        {"assets/characters/combat_sprites/samurai/Dead.png",
            6, 768, 128, 128, 1},
        {"assets/characters/combat_sprites/samurai/Hurt.png",
            3, 384, 128, 128, 1},
        {"assets/characters/combat_sprites/samurai/Attack_1.png",
            4, 512, 128, 128, 1},
        {"assets/characters/combat_sprites/samurai/Attack_2.png",
            5, 640, 128, 128, 1},
        {"assets/characters/combat_sprites/samurai/Attack_3.png",
            4, 512, 128, 128, 1},
        {"assets/characters/combat_sprites/samurai/Protection.png",
            2, 256, 128, 128, 1},
    },
    {
        {"assets/characters/combat_sprites/fire_wizard/Idle.png",
            7, 896, 128, 128, 1},
        {"assets/characters/combat_sprites/fire_wizard/Dead.png",
            6, 768, 128, 128, 1},
        {"assets/characters/combat_sprites/fire_wizard/Hurt.png",
            3, 384, 128, 128, 1},
        {"assets/characters/combat_sprites/fire_wizard/Attack_1.png",
            4, 512, 128, 128, 1},
        {"assets/characters/combat_sprites/fire_wizard/Attack_2.png",
            4, 512, 128, 128, 1},
        {"assets/characters/combat_sprites/fire_wizard/Fireball.png",
            8, 1024, 128, 128, 1},
        {"assets/characters/combat_sprites/fire_wizard/Flame_jet.png",
            14, 1792, 128, 128, 1},
    },
    {
        {"assets/characters/combat_sprites/lightning_mage/Idle.png",
            7, 896, 128, 128, 1},
        {"assets/characters/combat_sprites/lightning_mage/Dead.png",
            5, 640, 128, 128, 1},
        {"assets/characters/combat_sprites/lightning_mage/Hurt.png",
            3, 384, 128, 128, 1},
        {"assets/characters/combat_sprites/lightning_mage/Attack_1.png",
            10, 1280, 128, 128, 1},
        {"assets/characters/combat_sprites/lightning_mage/Attack_2.png",
            4, 512, 128, 128, 1},
        {"assets/characters/combat_sprites/lightning_mage/Light_ball.png",
            7, 896, 128, 128, 1},
        {"assets/characters/combat_sprites/lightning_mage/Light_charge.png",
            12, 1536, 128, 128, 1},
    },
    {
        {"assets/characters/combat_sprites/samurai_archer/Idle.png",
            9, 1152, 128, 128, 1},
        {"assets/characters/combat_sprites/samurai_archer/Dead.png",
            5, 640, 128, 128, 1},
        {"assets/characters/combat_sprites/samurai_archer/Hurt.png",
            3, 384, 128, 128, 1},
        {"assets/characters/combat_sprites/samurai_archer/Attack_1.png",
            5, 640, 128, 128, 1},
        {"assets/characters/combat_sprites/samurai_archer/Attack_2.png",
            5, 640, 128, 128, 1},
        {"assets/characters/combat_sprites/samurai_archer/Attack_3.png",
            6, 768, 128, 128, 1},
        {"assets/characters/combat_sprites/samurai_archer/Shot.png",
            14, 1792, 128, 128, 1},
    },
    {
        {"assets/characters/combat_sprites/samurai_commander/Idle.png",
            5, 640, 128, 128, 1},
        {"assets/characters/combat_sprites/samurai_commander/Dead.png",
            6, 768, 128, 128, 1},
        {"assets/characters/combat_sprites/samurai_commander/Hurt.png",
            2, 256, 128, 128, 1},
        {"assets/characters/combat_sprites/samurai_commander/Attack_1.png",
            4, 512, 128, 128, 1},
        {"assets/characters/combat_sprites/samurai_commander/Attack_2.png",
            5, 640, 128, 128, 1},
        {"assets/characters/combat_sprites/samurai_commander/Attack_3.png",
            4, 512, 128, 128, 1},
        {"assets/characters/combat_sprites/samurai_commander/Protect.png",
            2, 256, 128, 128, 1},
    },
    {
        {"assets/characters/combat_sprites/ninja_monk/Idle.png",
            7, 672, 96, 96, 1},
        {"assets/characters/combat_sprites/ninja_monk/Dead.png",
            5, 480, 96, 96, 1},
        {"assets/characters/combat_sprites/ninja_monk/Hurt.png",
            4, 384, 96, 96, 1},
        {"assets/characters/combat_sprites/ninja_monk/Attack_1.png",
            5, 480, 96, 96, 1},
        {"assets/characters/combat_sprites/ninja_monk/Attack_2.png",
            5, 480, 96, 96, 1},
        {"assets/characters/combat_sprites/ninja_monk/Blade.png",
            6, 576, 96, 96, 1},
        {"assets/characters/combat_sprites/ninja_monk/Cast.png",
            5, 480, 96, 96, 1},
    },
    {
        {"assets/characters/combat_sprites/kunoichi/Idle.png",
            9, 1152, 128, 128, 1},
        {"assets/characters/combat_sprites/kunoichi/Dead.png",
            5, 640, 128, 128, 1},
        {"assets/characters/combat_sprites/kunoichi/Hurt.png",
            2, 256, 128, 128, 1},
        {"assets/characters/combat_sprites/kunoichi/Attack_1.png",
            6, 768, 128, 128, 1},
        {"assets/characters/combat_sprites/kunoichi/Attack_2.png",
            6, 768, 128, 128, 1},
        {"assets/characters/combat_sprites/kunoichi/Cast.png",
            6, 768, 128, 128, 1},
        {"assets/characters/combat_sprites/kunoichi/Eating.png",
            9, 1152, 128, 128, 1},
    },
    {
        {"assets/characters/combat_sprites/skeleton_warrior/Idle.png",
            7, 896, 128, 128, 1},
        {"assets/characters/combat_sprites/skeleton_warrior/Dead.png",
            4, 512, 128, 128, 1},
        {"assets/characters/combat_sprites/skeleton_warrior/Hurt.png",
            2, 256, 128, 128, 1},
        {"assets/characters/combat_sprites/skeleton_warrior/Attack_1.png",
            5, 640, 128, 128, 1},
        {"assets/characters/combat_sprites/skeleton_warrior/Attack_2.png",
            6, 768, 128, 128, 1},
        {"assets/characters/combat_sprites/skeleton_warrior/Attack_3.png",
            4, 512, 128, 128, 1},
        {"assets/characters/combat_sprites/skeleton_warrior/Protect.png",
            1, 128, 128, 128, 1},
    },
    {
        {"assets/characters/combat_sprites/skeleton_spearman/Idle.png",
            7, 896, 128, 128, 1},
        {"assets/characters/combat_sprites/skeleton_spearman/Dead.png",
            5, 640, 128, 128, 1},
        {"assets/characters/combat_sprites/skeleton_spearman/Hurt.png",
            3, 384, 128, 128, 1},
        {"assets/characters/combat_sprites/skeleton_spearman/Attack_1.png",
            4, 512, 128, 128, 1},
        {"assets/characters/combat_sprites/skeleton_spearman/Attack_2.png",
            4, 512, 128, 128, 1},
        {"assets/characters/combat_sprites/skeleton_spearman/Fall.png",
            6, 768, 128, 128, 1},
        {"assets/characters/combat_sprites/skeleton_spearman/Protect.png",
            2, 256, 128, 128, 1},
    },
    {
        {"assets/characters/combat_sprites/skeleton_archer/Idle.png",
            7, 896, 128, 128, 1},
        {"assets/characters/combat_sprites/skeleton_archer/Dead.png",
            5, 640, 128, 128, 1},
        {"assets/characters/combat_sprites/skeleton_archer/Hurt.png",
            2, 256, 128, 128, 1},
        {"assets/characters/combat_sprites/skeleton_archer/Attack_1.png",
            5, 640, 128, 128, 4},
        {"assets/characters/combat_sprites/skeleton_archer/Shot_1.png",
            15, 1920, 128, 128, 13},
        {"assets/characters/combat_sprites/skeleton_archer/Shot_2.png",
            15, 1920, 128, 128, 13},
        {"assets/characters/combat_sprites/skeleton_archer/Evasion.png",
            6, 768, 128, 128, 3},
    },
    {
        {"assets/characters/combat_sprites/karasu_tengu/Idle.png",
            6, 768, 128, 128, 1},
        {"assets/characters/combat_sprites/karasu_tengu/Dead.png",
            6, 768, 128, 128, 1},
        {"assets/characters/combat_sprites/karasu_tengu/Hurt.png",
            3, 384, 128, 128, 1},
        {"assets/characters/combat_sprites/karasu_tengu/Attack_1.png",
            6, 768, 128, 128, 1},
        {"assets/characters/combat_sprites/karasu_tengu/Attack_2.png",
            3, 384, 128, 128, 1},
        {"assets/characters/combat_sprites/karasu_tengu/Attack_2.png",
            4, 512, 128, 128, 1},
        {"assets/characters/combat_sprites/karasu_tengu/Idle_2.png",
            5, 640, 128, 128, 1},
    },
};

#endif
