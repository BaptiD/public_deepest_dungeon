/*
** EPITECH PROJECT, 2024
** B-MUL-200-PAR-2-1-myrpg-pierre.pruvost
** File description:
** impact_frame.c
*/

#include "capacity.h"

sfBool is_impact_frame(combat_t *info, cap_info_t *cap)
{
    int index_animation = info->field[info->turn]->id + info->capa_pressed + 3;
    int actual_frame = info->field[info->turn]->rect.left /
        COMBAT_ANIMATION[index_animation]->frame_x;

    if (actual_frame == COMBAT_ANIMATION[index_animation]->impact_frame) {
        for (int i = 0; i < NB_ENTITY_SQUAD * 2; ++i) {
            if (info->field[i] != NULL && info->field[i]->status == IDLE && cap->type[i] == BASIC || cap->type[i] == CRIT) {
                hit_animation(info, i);
            }
        }
        return sfTrue;
    }
    return sfFalse;
}
