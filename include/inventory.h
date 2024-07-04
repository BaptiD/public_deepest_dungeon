/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** statics.h
*/

#ifndef INVENTORY_H_
    #define INVENTORY_H_
    #include <SFML/Graphics.h>
    #include "entity.h"

    #define OFF -1
    #define EMPTY -1

    #define NAME_SIZE 30
    #define PREV_STATS_SIZE 20
    #define STATS_SIZE 25
    #define STAT_LVL_SIZE 25
    #define ITEM_NAME_SIZE 27
    #define INFO_TITLE 27
    #define ITEM_DESCRIPTION_SIZE 22

    #define NB_ITEMS_MEMBER 3
    #define NB_SPELLS_MEMBER 4
    #define NB_POS 4

    #define BUFF_COLOR (sfColor){150, 0, 0, 255}

///////////// SELECTION INDEXES ///////////////
    #define ITEM_SELECT 0
    #define MEMBER_SELECT 1
    #define SPELL_SELECT 2

    #define FULL_SIZE (sfVector2f){1, 1}
    #define HALF_SIZE (sfVector2f){0.5, 0.5}
    #define DOUBLE_SIZE (sfVector2f){2, 2}
////////// DISPLAY MEMBERS //////////
/* DISPLAY MEMBER POSITIONS */
static const sfVector2f MEMBER_POS[NB_ENTITY_SQUAD] = {
    {573, 89},
    {890, 89},
    {1207, 89},
    {1524, 89}
};
/* DISPLAY MEMBER INFORMATIONS */
    #define MEMBER_NAME_OFST (sfVector2f){147, 23}
    #define MEMBER_INV_OFST (sfVector2f){13, 397}
    #define MEMBER_HP_BAR_OFST (sfVector2f){13, 489}
    #define MEMBER_HP_TXT_OFST (sfVector2f){13, 501}
    #define MEMBER_XP_BAR_OFST (sfVector2f){13, 536}
    #define MEMBER_XP_TXT_OFST (sfVector2f){13, 548}
    #define MEMBER_LEVEL_OFST (sfVector2f){147, 583}
/* MEMBER ENTITY SIZE */
    #define MEMBER_SIZE (sfVector2f){297, 643}
    #define MEMBER_PIC_SIZE (sfVector2f){284, 316}

static const sfVector2f MEMBER_ITEM_OFST[] = {
    {13, 397},
    {59, 397},
    {105, 397}
};
/* MEMBER EQ ITEMS SIZE */
    #define MEMBER_ITEM_SIZE (sfVector2f){50, 50}
    #define MEMBER_INV_SIZE (sfVector2f){142, 50}
/* MEMBER PICS RATIO SIZES */
static const sfVector2f MEMBER_PIC_RATIO[] = {
    {5, 5},
    {4.2, 4.2},
    {4, 4},
    {3.6, 3.6},//Samurai
    {4, 4}, //fire wizard
    {4, 4}, //mage
    {4, 4},
    {4, 4},
    {4, 4},
    {4, 4},
    {4, 4},
    {4, 4},
    {4, 4},
    {3.5, 3.5}
};

static const sfVector2f MEMBER_PIC_OFST[] = {
    {-100, 383},
    {-120, 383},
    {-35, 383},
    {35, 383},//Samurai
    {-50, 383},
    {-65, 383},
    {-95, 383},
    {-90, 383},
    {-40, 383},
    {-93, 383},
    {-95, 383},
    {-81, 383},
    {-85, 383},
    {-98, 383}
};

//////////// DISPLAY ITEMS /////////////////
/* DISPLAY ITEMS POSITIONS */
static const sfVector2f ITEM_POS[INVENTORY_SIZE] = {
    {70, 67},
    {190, 67},
    {310, 67},
    {70, 187},
    {190, 187},
    {310, 187},
    {70, 307},
    {190, 307},
    {310, 307},
    {70, 427},
    {190, 427},
    {310, 427}
};
/* DISPLAY ITEM INFORMATIONS */
    #define ITEM_NAME_POS (sfVector2f){55, 581}
    #define ITEM_DESCRIPTION_POS (sfVector2f){55, 637}
/* ITEM ENTITY SIZE */
    #define ITEM_SIZE (sfVector2f){100, 100}

////////////// DISPLAY SPELLS ///////////////
/* DISPLAY SPELLS SQUARES */
static const sfVector2f SPELL_POS[] = {
    {961, 820},
    {1026, 820},
    {1091, 820},
    {1156, 820}
};
/* SPELLS SQUARES SIZE */
    #define SPELL_SIZE (sfVector2f){50, 50}
/* DISPLAY SPELLS TITLE */
    #define MEMBER_STATS_TITLE (sfVector2f){580, 771}
    #define MEMBER_SPELL_TITLE (sfVector2f){964, 771}

/* DISPLAY SPELLS INFORMATIONS */
    #define SPELL_NAME (sfVector2f){1236, 820}
    #define SPELL_RANGE (sfVector2f){1061, 910}
    #define SPELL_FOCUS (sfVector2f){1296, 910}
    #define SPELL_PLACE_OFST (sfVector2f){52, 0}

///////////////// DISPLAY STATS //////////////////
/* STATS POS */
static const sfVector2f STATS_POS[] = {
    {55, 820},
    {575, 820},
    {1550, 820}
};
/* DISPLAY STATS CONTENT */
    #define STAT_HEART_OFST (sfVector2f){58, 3}
    #define STAT_PROTECTION_OFST (sfVector2f){58, 59}
    #define STAT_SPEED_OFST (sfVector2f){58, 115}
    #define STAT_ATTACK_OFST (sfVector2f){200, 3}
    #define STAT_CRITICAL_OFST (sfVector2f){200, 59}
    #define STAT_PRECISION_OFST (sfVector2f){200, 115}

static const sfVector2f STAT_OFST[] = {
    {58, 3},
    {200, 3},
    {58, 59},
    {200, 59},
    {58, 115},
    {200, 115}
};

static const int STAT_SPR_INDEX[] = {
    STAT_HEALTH,
    STAT_ATTACK,
    STAT_CRITIC,
    STAT_PRECISION,
    STAT_PROTECTION,
    STAT_SPEED
};
/* STATS DIFFERENTS INDEXES FOR EACH USAGE IN POSITIONS TAB */
    #define ITEM_STATS_POS 0
    #define MEMBER_STATS_POS 1
    #define SPELL_STATS_POS 2

int confirmation(display_t *display, entity_t *player, int *selection);

int drag_n_drop_member(display_t *display, entity_t *player, int *selection,
    int index_click);
int drag_n_drop_item(display_t *display, entity_t *player, int *selection,
    int id);

//////////////////// INVENTORY DISPLAYS ////////////////////
void display_squad(display_t *display, entity_t *player, sfText *text,
    int *selection);
void display_buttons(display_t *display, entity_t *player, int *selection);
void display_selection(display_t *display, entity_t *player, sfText *text,
    int *selection);
void display_items(display_t *display, entity_t *player, sfText *text,
    int *selection);
void display_member_stats(display_t *display, sfText *text, stats_t stats,
    int *items);
void display_part_stats(display_t *display, sfText *text, stats_t stats,
    sfVector2f pos);
void check_eq_item(display_t *display, sfVector2f member_pos, sfVector2i pos,
    int index);
void remove_item(entity_t *player, int item);
void remove_stats(entity_t *player, int id, int dest);

bool manage_click_spells(display_t *display, entity_t *player,
    int *selection, sfVector2i pos);
bool manage_click_items(display_t *display, entity_t *player, int *selection,
    sfVector2i pos);
bool manage_click_members(display_t *display, entity_t *player,
    int *selection, sfVector2i pos);

static const int SPRITES_INDEXES[] = {
    FIRE_KNIGHT_S,
    WIZARD_WANDERER_S,
    NINJA_PEASANT_S,
    SAMURAI_S,
    FIRE_WIZARD_S,
    LIGHTNING_MAGE_S,
    SAMURAI_ARCHER_S,
    SAMURAI_COMMANDER_S,
    NINJA_MONK_S,
    KUNOICHI_S,
    SQ_WARRIOR_S,
    SQ_SPEAR_S,
    SQ_ARC_S,
    KARASU_S
};

#endif
