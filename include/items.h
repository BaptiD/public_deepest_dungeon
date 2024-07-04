/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** statics.h
*/

#ifndef ITEMS_H_
    #define ITEMS_H_
    #include "entity.h"
    #include "sprites.h"

    #define NB_ITEMS 25
    #define ACTIVE 1
    #define PASSIVE 2

    #define ITEM_CHEST_CHANCE 90
    #define ITEM_COMBAT_CHANCE 10
    #define ITEM_CHEST_START_POS (sfVector2f){910, 700}
    #define ITEM_CHEST_END_POS (sfVector2f){910, 500}
    #define CHEST_ANIMATION_SPEED 0.10
    #define ITEM_SPAWNING_SPEED 0.02
    #define OBTAINED_ITEM_STATS_POS (sfVector2f){100, 900}
    #define CHEST_OPEN_ITEM_NAME (sfVector2f){960, 100}

static const int ITEM_SPRITE[NB_ITEMS] = {
    BLACK_BOOK,
    BLUE_RELIC,
    BROWN_BOOK,
    GOLD_RELIC,
    GREEN_POTION,
    LETTER,
    MEDAL,
    RED_BOOK,
    RED_POTION,
    SHIELD,
    STONE,
    TROPHY,
    RABADON,
    NECKLACE_1,
    NECKLACE_2,
    NECKLACE_3,
    NECKLACE_4,
    RING_1,
    RING_2,
    RING_3,
    SCROLL_1,
    SCROLL_2,
    SCROLL_3,
    SKULL,
    VOID_SAFF,
};

static const char *ITEM_NAME[NB_ITEMS] = {
    "Obsidian Grimoire",
    "Blue Relic",
    "Brown Book",
    "Gold Relic",
    "Green Potion",
    "Letter",
    "Medal",
    "Red Book",
    "Red Potion",
    "Shield",
    "Stone",
    "Trophy",
    "Rabadon Deathcap",
    "Leaf Necklace",
    "Fire Necklace",
    "Water Necklace",
    "Golden Necklace",
    "Golden Ring",
    "Volcanic Ring",
    "Natural Ring",
    "Infernal Scroll",
    "Ocean Scroll",
    "Lightning Scroll",
    "Explorer Skull",
    "Void Staff"
};

static const char *ITEM_DESCRIPTION[NB_ITEMS] = {
    "A relic of ancient power, shrouded in\nmystery and fear.",
    "Description of the Blue Relic",
    "Description of the Brown Book",
    "Description of the Gold Relic",
    "Description of the Green Potion",
    "Description of the Letter",
    "Description of the Medal",
    "Description of the Red Book",
    "Description of the Red Potion",
    "Description of the Shield",
    "Description of the Stone",
    "Description of the Trophy",
    "Description",
    "Description",
    "Description",
    "Description",
    "Description",
    "Description",
    "Description",
    "Description",
    "Description",
    "Description",
    "Description",
    "Description",
    "Description",
};

static const stats_t ITEM_STATS[NB_ITEMS] = {
    {2, -10, 0, 0, 5, 0},       //Black Book
    {0, 8, 0, 0, 0, 5},         //Blue Relic
    {1, 5, 0, 0, 0, 0},         //Brown Book
    {0, 0, 0, 0, 7, 0},         //Gold Relic
    {0, 0, 2, 0, 0, 0},         //Green Potion
    {0, 0, 0, 0, 0, 0},         //Letter
    {0, 0, 0, 0, 10, 0},        //Medal
    {0, 10, 0, 0, -5, 0},       //Red Book
    {0, 6, 0, 0, 0, 0},         //Red Potion
    {0, 0, -1, 0, 0, 20},       //Shield
    {-2, 30, -1, -20, 0, 30},   //Stone
    {0, 0, 0, 5, 5, -10},       //Trophy
    {5, 0, 0, 0, 0, 0},         //Rabadon
    {0, 10, 0, 0, 0, 0},        //Leaf Necklace
    {0, 0, 0, 5, 0, 0},         //Fire Necklace
    {0, 0, 1, 0, 3, 0},         //Water Necklace
    {1, -3, 1, 1, -3, -3},      //Golden Neclace
    {0, 0, 0, 5, 5, 0},         //Golden Ring
    {1, 0, 0, 10, -5, 0},       //Volcanic Ring
    {0, 5, 0, 0, 5, 0},         //Natural Ring
    {2, 0, 0, 5, 0, 0},         //Infernal Scroll
    {0, 0, 0, 0, 0, 20},        //Ocean Scroll
    {0, 0, 1, 0, 5, 0},         //Lightning Scroll
    {-1, 0, 2, -10, 5, 5},       //Explorer Skull
    {0, 0, 0, 15, 0, 0},        //Void Staff
};

// Get an item in a chest
int get_random_nb(int n, int m);

#endif
