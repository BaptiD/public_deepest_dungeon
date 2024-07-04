/*
** EPITECH PROJECT, 2024
** B-MUL-200-PAR-2-1-myrpg-pierre.pruvost
** File description:
** setup_combat.c
*/
#include "combat.h"
#include "my.h"

static void set_rect_to_combat(combat_t *info)
{
    for (int i = 0; i < NB_ENTITY_SQUAD * 2; ++i) {
        if (info->field[i] != NULL)
            info->field[i]->rect = (sfIntRect){0, 0,
                COMBAT_ANIMATION[info->field[i]->id]->frame_x,
                COMBAT_ANIMATION[info->field[i]->id]->y_max};
    }
}

sprite_t set_background(void)
{
    sprite_t background = {0};

    logs(INFO, "Setting background map...");
    background.sprite = sfSprite_create();
    background.texture = sfTexture_createFromFile(COMBAT_BG, NULL);
    sfSprite_setTexture(background.sprite, background.texture, sfTrue);
    sfSprite_setPosition(background.sprite, COMBAT_BG_POS);
    logs(SUCCESS, "Bacground set OK");
    return background;
}

static void set_random_rect_left(entity_t *entity)
{
    entity->rect.left = arc4random() % COMBAT_ANIMATION[entity->id][IDLE]
        .nb_anim * COMBAT_ANIMATION[entity->id][IDLE].y_max;
}

static void set_field_player(combat_t *info, entity_t *player)
{
    for (int i = 0; i < NB_ENTITY_SQUAD; ++i) {
        if (player->squad[i] != NULL) {
            info->field[i] = player->squad[i];
            set_random_rect_left(info->field[i]);
            sfSprite_setPosition(info->field[i]->display[COMBAT_STATE]->sprite,
                (sfVector2f){ENTITY_DISTANCE * i, ENTITY_POS_Y});
        } else
            info->field[i] = NULL;
    }
}

static void set_field_monster(combat_t *info, entity_t *monster)
{
    int ind = NB_ENTITY_SQUAD;
    sfVector2f ratio = {0};

    for (int i = 7; i > NB_ENTITY_SQUAD - 1; --i) {
        if (monster->squad[i - NB_ENTITY_SQUAD] != NULL) {
            info->field[ind] = monster->squad[i - NB_ENTITY_SQUAD];
            ratio.x = -(COMBAT_SPRITE_SIZE / COMBAT_ANIMATION
                [info->field[ind]->id][IDLE].frame_x);
            ratio.y = COMBAT_SPRITE_SIZE / COMBAT_ANIMATION
                [info->field[ind]->id][IDLE].frame_x;
            sfSprite_setScale(info->field[ind]->display[COMBAT_STATE]
                ->sprite, ratio);
            set_random_rect_left(info->field[ind]);
            sfSprite_setPosition(info->field[ind]->display[COMBAT_STATE]->
                sprite, (sfVector2f){(ENTITY_DISTANCE * ind) + MONSTER_POS_X - COMBAT_SPRITE_SIZE, ENTITY_POS_Y});
        } else
            info->field[ind] = NULL;
        ind += 1;
    }
}

static int *set_played_indicator(void)
{
    int *indicator = malloc(sizeof(int) * (NB_ENTITY_SQUAD * 2));

    for (int i = 0; i < NB_ENTITY_SQUAD * 2; ++i)
        indicator[i] = WAIT;
    return indicator;
}

combat_t *set_combat(entity_t *player, entity_t *monster)
{
    combat_t *combat = malloc(sizeof(combat_t));

    logs(INFO, "Setting combat info...");
    combat->background = set_background();
    combat->field = malloc(sizeof(entity_t) * NB_ENTITY_SQUAD * 2);
    set_field_player(combat, player);
    set_field_monster(combat, monster);
    combat->clock = sfClock_create();
    combat->index_clock = 0;
    combat->turn = -1;
    combat->played = set_played_indicator();
    combat->capa_pressed = 0;
    set_rect_to_combat(combat);
    logs(SUCCESS, "Combat set OK");
    return combat;
}
