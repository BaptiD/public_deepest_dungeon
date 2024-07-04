/*
** EPITECH PROJECT, 2024
** B-MUL-200-PAR-2-1-myrpg-pierre.pruvost
** File description:
** create_monster_squad.c
*/

#include "combat.h"
#include "my.h"

static int get_difficulty_squad(entity_t **squad)
{
    int squad_lvl = 0;

    for (int i = 0; i < NB_ENTITY_SQUAD; ++i) {
        if (squad[i] != NULL)
            squad_lvl += squad[i]->level;
    }
    return squad_lvl;
}

static void lvl_up_random_monster(entity_t *monster)
{
    int random_monster = arc4random() % 4;

    while (monster->squad[random_monster] == NULL) {
        random_monster = arc4random() % 4;
    }
    monster->squad[random_monster]->level += 1;
    monster->squad[random_monster]->stats->hp += 3;
    level_up_entity(monster->squad[random_monster], NULL, MONSTER_ENTITY, 1);
}

static sfBool is_squad_full(entity_t **squad)
{
    for (int i = 0; i < NB_ENTITY_SQUAD; ++i) {
        if (squad[i] == NULL)
            return sfFalse;
    }
    return sfTrue;
}

static int get_place_monster(entity_t *monster, int id)
{
    int index = -1;

    for (int i = 0; i < NB_ENTITY_SQUAD; ++i) {
        if (monster->squad[i] == NULL && MONSTER_POS[id - 10][i]) {
            index = i;
            break;
        }
    }
    return index;
}

static void add_random_monster(entity_t *monster)
{
    int index = -1;
    int random_monster = get_random_nb(SQ_WARRIOR, SQ_ARC);

    while (index == -1) {
        random_monster = get_random_nb(SQ_WARRIOR, SQ_ARC);
        index = get_place_monster(monster, random_monster);
    }
    monster->squad[index] = setting_entity_from_file(random_monster);
}

static entity_t *set_random_monster(entity_t *player)
{
    entity_t *monster = NULL;
    int diff_squad = get_difficulty_squad(player->squad);
    int difficulty = arc4random() % (0 - (-1) + 1) + (-1) + diff_squad - 1;
    int index = 0;
    int add_entity = 0;

    monster = setting_entity_from_file(get_random_nb(SQ_WARRIOR, SQ_ARC));
    index = get_place_monster(monster, monster->id);
    swap_entity(monster, NB_ENTITY_SQUAD - 1, index);
    while (difficulty > 0) {
        add_entity = arc4random() % 3;
        if (add_entity == 1 && is_squad_full(monster->squad) == sfFalse) {
            add_random_monster(monster);
        } else {
            lvl_up_random_monster(monster);
        }
        difficulty -= 1;
    }
    logs(SUCCESS, "Monster set OK");
    return monster;
}

static entity_t *set_boss_squad(int boss)
{
    entity_t *monster = NULL;

    if (boss == BOSS_KARASU) {
        monster = setting_entity_from_file(KARASU);
        monster->squad[0] = setting_entity_from_file(SQ_ARC);
        monster->squad[1] = setting_entity_from_file(SQ_ARC);
    }
    if (monster == NULL)
        monster = setting_entity_from_file(SQ_WARRIOR);
    return monster;
}

entity_t *set_monster_squad(entity_t *player, int boss)
{
    entity_t *monster = NULL;

    if (boss < 0) {
        monster = set_random_monster(player);
    } else {
        monster = set_boss_squad(boss);
    }
    return monster;
}
