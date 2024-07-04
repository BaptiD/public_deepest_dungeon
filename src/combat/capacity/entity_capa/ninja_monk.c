/*
** EPITECH PROJECT, 2024
** B-MUL-200-PAR-2-1-myrpg-pierre.pruvost
** File description:
** ninja_monk.c
*/

#include "combat.h"
#include "capacity.h"

void nm_kill_front(combat_t *info, int self, int focus, cap_info_t *cap)
{
    if (info->field[focus] != NULL && info->field[focus]->status != DEAD) {
        attack_entity(info, focus, cap, 4);
    }
}

void nm_backblade(combat_t *info, int self, int focus, cap_info_t *cap)
{
    int crit_temp = info->field[self]->mod->crt;

    info->field[self]->mod->crt = 100;
    if (info->field[focus] != NULL && info->field[focus]->status != DEAD) {
        attack_entity(info, focus, cap, 0);
    }
    info->field[self]->mod->crt = crit_temp;
}

void nm_canalisation(combat_t *info, int self, int focus, cap_info_t *cap)
{
    info->field[self]->mod->spd += 2;
    cap->entity_hit[self] = 2;
    cap->type[self] = STAT_UP;
}
