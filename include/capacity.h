/*
** EPITECH PROJECT, 2024
** B-MUL-200-PAR-2-1-myrpg-pierre.pruvost
** File description:
** capacity.h
*/

#ifndef CAPACITY_H_
    #define CAPACITY_H_

    #include "combat.h"

//////////////// FUNCTIONS ////////////////

/* Capacity interaction */
cap_info_t *launch_capacity(combat_t *info, int focus, int capacity_index,
    int capa_id);

/* Capacity Usage */
void attack_entity(combat_t *info, int focus, cap_info_t *cap, int mod);
sfBool crit_chance(entity_t *entity);
sfBool is_hitting(entity_t *entity);

//////////////// CAPACITIES ////////////////

/* Basic attack */
void ally_basic_attack(combat_t *info, int self, int focus, cap_info_t *cap);
void monster_basic_attack(combat_t *info, int self, int focus,
    cap_info_t *cap);

/* Fire Knight */
void kf_fire_ball(combat_t *info, int self, int focus, cap_info_t *cap);
void kf_flame_blade(combat_t *info, int self, int focus, cap_info_t *cap);
void kf_block(combat_t *info, int self, int focus, cap_info_t *cap);

/* Fire Wizard */
void fw_back_slash(combat_t *info, int self, int focus, cap_info_t *cap);
void fw_fire_ball(combat_t *info, int self, int focus, cap_info_t *cap);
void fw_flame_throw(combat_t *info, int self, int focus, cap_info_t *cap);

/* Kunoichi */
void k_slow(combat_t *info, int self, int focus, cap_info_t *cap);
void k_heal(combat_t *info, int self, int focus, cap_info_t *cap);
void k_throw_enscent(combat_t *info, int self, int focus, cap_info_t *cap);

/* Lightning Mage */
void lm_blind_spark(combat_t *info, int self, int focus, cap_info_t *cap);
void lm_light_ball(combat_t *info, int self, int focus, cap_info_t *cap);
void lm_paralyze(combat_t *info, int self, int focus, cap_info_t *cap);

/* Ninja Monk */
void nm_kill_front(combat_t *info, int self, int focus, cap_info_t *cap);
void nm_backblade(combat_t *info, int self, int focus, cap_info_t *cap);
void nm_canalisation(combat_t *info, int self, int focus, cap_info_t *cap);

/* Ninja Peasant */
void np_knif(combat_t *info, int self, int focus, cap_info_t *cap);
void np_bunker(combat_t *info, int self, int focus, cap_info_t *cap);
void np_dart(combat_t *info, int self, int focus, cap_info_t *cap);

/* Samurai Archer */
void sa_slash(combat_t *info, int self, int focus, cap_info_t *cap);
void sa_hit(combat_t *info, int self, int focus, cap_info_t *cap);
void sa_arrow(combat_t *info, int self, int focus, cap_info_t *cap);

/* Samurai Commander */
void sc_basic(combat_t *info, int self, int focus, cap_info_t *cap);
void sc_motivation(combat_t *info, int self, int focus, cap_info_t *cap);
void sc_protect(combat_t *info, int self, int focus, cap_info_t *cap);

/* Samurai */
void s_heavy_hit(combat_t *info, int self, int focus, cap_info_t *cap);
void s_blind(combat_t *info, int self, int focus, cap_info_t *cap);
void s_protect(combat_t *info, int self, int focus, cap_info_t *cap);

/* Squeleton Archer */
void sqa_double_arr(combat_t *info, int self, int focus, cap_info_t *cap);
void sqa_heavy_arrow(combat_t *info, int self, int focus, cap_info_t *cap);
void sqa_dodge(combat_t *info, int self, int focus, cap_info_t *cap);

/* Squeleton Spear */
void sqs_reach(combat_t *info, int self, int focus, cap_info_t *cap);
void sqs_break_gruard(combat_t *info, int self, int focus, cap_info_t *cap);
void sqs_protect(combat_t *info, int self, int focus, cap_info_t *cap);

/* Squeleton Warrior */
void sqw_breaker(combat_t *info, int self, int focus, cap_info_t *cap);
void sqw_bleeder(combat_t *info, int self, int focus, cap_info_t *cap);
void sqw_protect(combat_t *info, int self, int focus, cap_info_t *cap);

/* Wizard Wanderer */
void ww_smoke_screen(combat_t *info, int self, int focus, cap_info_t *cap);
void ww_air_speed(combat_t *info, int self, int focus, cap_info_t *cap);
void ww_wind_slash(combat_t *info, int self, int focus, cap_info_t *cap);

/* Karasu Tengu */
void kt_bleeder(combat_t *info, int self, int focus, cap_info_t *cap);
void kt_slash(combat_t *info, int self, int focus, cap_info_t *cap);
void kt_crow_eye(combat_t *info, int self, int focus, cap_info_t *cap);

//////////////// SPRITES CAPACITIES ////////////////

    #define NB_CAPA_BY_ENTITY 4
    #define CAPA_INDI_Y 950
    #define CAPA_INDI_X 540
    #define CAPA_INDI_SEPARATOR 35

static const sfVector2f CAPA_POS_COMBAT[] = {
    {500, 820},
    {600, 820},
    {700, 820},
    {800, 820},
};

static const char *CAPA_DISP_PATH[] = {
    NULL,
    "assets/combat/icons/Buffs/attack_boost.png",
    "assets/combat/icons/Spells/summoning_spell.png",
    "assets/combat/icons/Debuffs/blinded.png",
    "assets/combat/icons/Buffs/swiftness.png",
    "assets/combat/icons/Buffs/magic_amplification.png",
    "assets/combat/icons/Spells/summoning_spell.png",
    "assets/combat/icons/Spells/summoning_spell.png",
    "assets/combat/icons/Spells/summoning_spell.png",
    "assets/combat/icons/Spells/fire_spell_2.png",
    "assets/combat/icons/Spells/fortify_spell.png",
    "assets/combat/icons/Spells/fire_spell.png",
    "assets/combat/icons/Buffs/glow.png",
    "assets/combat/icons/Spells/fire_spell_2.png",
    "assets/combat/icons/Spells/fire_spell.png",
    "assets/combat/icons/Debuffs/slowed.png",
    "assets/combat/icons/Buffs/lucky_boost.png",
    "assets/combat/icons/Buffs/regeneration.png",
    "assets/combat/icons/Spells/blinding_light_spell.png",
    "assets/combat/icons/Buffs/glow.png",
    "assets/combat/icons/Spells/lightning_spell.png",
    "assets/combat/icons/Buffs/knockback_boost.png",
    "assets/combat/icons/Buffs/critical_boost.png",
    "assets/combat/icons/Buffs/negative_status_resistance.png",
    "assets/combat/icons/Buffs/attack_speed_boost.png",
    "assets/combat/icons/Buffs/knockback_resistance.png",
    "assets/combat/icons/Spells/poison_dagger.png",
    "assets/combat/icons/Spells/poison_dagger.png",
    "assets/combat/icons/Buffs/attack_speed_boost.png",
    "assets/combat/icons/Buffs/knockback_boost.png",
    "assets/combat/icons/Buffs/attack_speed_boost.png",
    "assets/combat/icons/Buffs/negative_status_resistance.png",
    "assets/combat/icons/Spells/fortify_spell.png",
    "assets/combat/icons/Buffs/critical_boost.png",
    "assets/combat/icons/Debuffs/blinded.png",
    "assets/combat/icons/Spells/fortify_spell.png",
    "assets/combat/icons/Spells/summoning_spell.png",
    "assets/combat/icons/Spells/summoning_spell.png",
    "assets/combat/icons/Spells/summoning_spell.png",
    "assets/combat/icons/Spells/summoning_spell.png",
    "assets/combat/icons/Spells/summoning_spell.png",
    "assets/combat/icons/Spells/summoning_spell.png",
    "assets/combat/icons/Spells/summoning_spell.png",
    "assets/combat/icons/Spells/summoning_spell.png",
    "assets/combat/icons/Spells/summoning_spell.png",
};

//////////////// STRUCTURE ////////////////

enum type_target {
    SELECT,
    DEFINED,
    SELF
};

typedef struct capa_s {
    int type;
    char name[120];
    char description[1000];
    int range[NB_ENTITY_SQUAD * 2];
    int focus[NB_ENTITY_SQUAD * 2];
    void (*func)(combat_t *info, int self, int focus, cap_info_t *cap);
} capa_t;

//////////////// ARRAY ////////////////

static capa_t CAPACITY[] = {
    {
        0,
        "Void",
        "Void",
        {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0},
        NULL
    },
    {
        DEFINED,
        "Basic Attack",
        "Attack the first target reachable",
        {1, 1, 1, 1, 0, 0, 0, 0}, {0, 0, 0, 0, 1, 1, 1, 1},
        &ally_basic_attack
    },
    {
        DEFINED,
        "Monster Basic Attack",
        "Attack the first target reachable",
        {0, 0, 0, 0, 1, 1, 1, 1}, {1, 1, 1, 1, 0, 0, 0, 0},
        &monster_basic_attack
    },
    {
        DEFINED,
        "Smoke Screen",
        "Lower the precision of both monster in the middle",
        {1, 1, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 1, 1, 0},
        &ww_smoke_screen
    },
    {
        DEFINED,
        "Aspiration",
        "Speed up the team",
        {1, 1, 0, 0, 0, 0, 0, 0}, {1, 1, 1, 1, 0, 0, 0, 0},
        &ww_air_speed
    },
    {
        DEFINED,
        "Wind Slash",
        "Attack every target no matter the position for half damages",
        {1, 1, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 1, 1, 1, 1},
        &ww_wind_slash
    },
    {
        SELECT,
        "Bleeder",
        "Void",
        {0, 0, 0, 0, 1, 1, 0, 0}, {0, 1, 1, 1, 0, 0, 0, 0},
        &sqw_bleeder
    },
    {
        SELECT,
        "Breaker",
        "Void",
        {0, 0, 0, 0, 1, 1, 0, 0}, {0, 1, 1, 1, 0, 0, 0, 0},
        &sqw_breaker
    },
    {
        SELF,
        "Shield",
        "Void",
        {0, 0, 0, 0, 1, 1, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0},
        &sqw_protect
    },
    {
        SELECT,
        "Eruption",
        "Hit the target by your ATK (attack) - 3 and up your ATK by 1",
        {0, 0, 1, 1, 0, 0, 0, 0}, {0, 0, 0, 0, 1, 1, 0, 0},
        &kf_fire_ball
    },
    {
        SELECT,
        "Fire Protection",
        "Up the PRO (protection) of the target by 8",
        {0, 0, 1, 1, 0, 0, 0, 0}, {0, 0, 1, 1, 0, 0, 0, 0},
        &kf_block
    },
    {
        DEFINED,
        "Volcan Blade",
        "Hit the first two target and reduce the bonus ATK (attack)\nto 0",
        {0, 0, 1, 1, 0, 0, 0, 0}, {0, 0, 0, 0, 1, 1, 0, 0},
        &kf_flame_blade
    },
    {
        DEFINED,
        "Back Slash",
        "Hit the last target",
        {1, 1, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 1, 1, 1, 1},
        &fw_back_slash
    },
    {
        DEFINED,
        "Fire Ball",
        "Hit the last two target by your ATK (attack) - 2 and have\n60% chance to burn them",
        {1, 1, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 1, 1},
        &fw_fire_ball
    },
    {
        DEFINED,
        "Flame Throw",
        "Hit the first two target by your ATK (attack) - 2 and lower\ntheir PRE (precision) by 2",
        {1, 1, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 1, 1, 0, 0},
        &fw_flame_throw
    },
    {
        SELECT,
        "Ankle Catcher",
        "Hit the target by your ATK (attack) - 2 and lower his speed\nby 2",
        {1, 1, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 1, 1, 1, 0},
        &k_slow
    },
    {
        DEFINED,
        "Enscent",
        "Heal all of your group by 2-4 HP",
        {1, 1, 0, 0, 0, 0, 0, 0}, {1, 1, 1, 1, 0, 0, 0, 0},
        &k_throw_enscent
    },
    {
        SELECT,
        "Eating",
        "Heal a target by 4-6 HP",
        {1, 1, 0, 0, 0, 0, 0, 0}, {1, 1, 1, 1, 0, 0, 0, 0},
        &k_heal
    },
    {
        DEFINED,
        "Blinding Spark",
        "Blind the first two target and lower theire PRE (precision)\n by 4",
        {0, 1, 1, 1, 0, 0, 0, 0}, {0, 0, 0, 0, 1, 1, 0, 0},
        &lm_blind_spark
    },
    {
        DEFINED,
        "Lightning Ball",
        "Hit every targets by your ATK (attack) - 2",
        {0, 1, 1, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 1, 1, 1, 1},
        &lm_light_ball
    },
    {
        DEFINED,
        "Paralyze",
        "Hit the first two target by your ATK (attack) - 3\n and lower theire SPD (speed) by 1",
        {0, 1, 1, 1, 0, 0, 0, 0}, {0, 0, 0, 0, 1, 1, 0, 0},
        &lm_paralyze
    },
    {
        DEFINED,
        "Assassinate",
        "Hit heavily the first target by your ATK (attack) + 4",
        {0, 1, 1, 1, 0, 0, 0, 0}, {0, 0, 0, 0, 1, 0, 0, 0},
        &nm_kill_front
    },
    {
        SELECT,
        "Shadow Blade",
        "Hit the target with 100% chance of CRT (critical chance)",
        {0, 0, 1, 1, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 1, 1},
        &nm_backblade
    },
    {
        SELF,
        "Canalisation",
        "Void",
        {1, 1, 1, 1, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0},
        &nm_canalisation
    },
    {
        SELECT,
        "Pocket Kniff",
        "Void",
        {1, 1, 1, 1, 0, 0, 0, 0}, {0, 0, 0, 0, 1, 1, 1, 0},
        &np_knif
    },
    {
        SELF,
        "Hiding Spot",
        "Void",
        {1, 1, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0},
        &np_bunker
    },
    {
        SELECT,
        "Poison Dart",
        "Void",
        {1, 1, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 1, 1, 1, 1},
        &np_dart
    },
    {
        DEFINED,
        "Bleeding Slash",
        "Void",
        {0, 0, 1, 1, 0, 0, 0, 0}, {0, 0, 0, 0, 1, 0, 0, 0},
        &sa_slash
    },
    {
        SELECT,
        "Hard Hit",
        "Void",
        {0, 0, 1, 1, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 1, 1, 0},
        &sa_hit
    },
    {
        DEFINED,
        "Arrow",
        "Void",
        {1, 1, 1, 1, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 1},
        &sa_arrow
    },
    {
        SELECT,
        "Hit",
        "Void",
        {0, 0, 1, 1, 0, 0, 0, 0}, {0, 0, 0, 0, 1, 1, 1, 0},
        &sc_basic
    },
    {
        DEFINED,
        "Galvanisation",
        "Void",
        {1, 1, 1, 1, 0, 0, 0, 0}, {1, 1, 1, 1, 0, 0, 0, 0},
        &sc_motivation
    },
    {
        DEFINED,
        "Protection",
        "Void",
        {1, 1, 1, 1, 0, 0, 0, 0}, {0, 0, 1, 1, 0, 0, 0, 0},
        &sc_protect
    },
    {
        SELECT,
        "Heavy Blade",
        "Void",
        {0, 0, 1, 1, 0, 0, 0, 0}, {0, 0, 0, 0, 1, 1, 0, 0},
        &s_heavy_hit
    },
    {
        SELECT,
        "Blinding Powder",
        "Void",
        {0, 0, 1, 1, 0, 0, 0, 0}, {0, 0, 0, 0, 1, 1, 0, 0},
        &s_blind
    },
    {
        SELF,
        "Protect",
        "Void",
        {1, 1, 1, 1, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0},
        &s_protect
    },
    {
        DEFINED,
        "Double Arrow",
        "Void",
        {0, 0, 0, 0, 0, 0, 1, 1}, {1, 1, 0, 0, 0, 0, 0, 0},
        &sqa_double_arr
    },
    {
        SELECT,
        "Heavy Arrow",
        "Void",
        {0, 0, 0, 0, 0, 0, 1, 1}, {1, 1, 1, 1, 0, 0, 0, 0},
        &sqa_heavy_arrow
    },
    {
        SELF,
        "Dodge",
        "Void",
        {0, 0, 0, 0, 0, 0, 1, 1}, {0, 0, 0, 0, 0, 0, 0, 0},
        &sqa_dodge
    },
    {
        SELECT,
        "Spear Reach",
        "Void",
        {0, 0, 0, 0, 1, 1, 1, 0}, {1, 1, 1, 0, 0, 0, 0, 0},
        &sqs_reach
    },
    {
        SELECT,
        "Guard Breaker",
        "Void",
        {0, 0, 0, 0, 1, 1, 1, 0}, {0, 1, 1, 1, 0, 0, 0, 0},
        &sqs_break_gruard
    },
    {
        SELF,
        "Defensive manouver",
        "Void",
        {0, 0, 0, 0, 1, 1, 1, 0}, {0, 0, 0, 0, 0, 0, 0, 0},
        &sqs_protect
    },
    {
        SELECT,
        "Bleeder",
        "Void",
        {0, 0, 0, 0, 1, 1, 0, 0}, {0, 0, 1, 1, 0, 0, 0, 0},
        &kt_bleeder
    },
    {
        DEFINED,
        "Slash",
        "Void",
        {0, 0, 0, 0, 1, 1, 0, 0}, {1, 1, 1, 1, 0, 0, 0, 0},
        &kt_slash
    },
    {
        SELF,
        "Crow Eye",
        "Void",
        {0, 0, 0, 0, 1, 1, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0},
        &kt_crow_eye
    },
};

#endif
