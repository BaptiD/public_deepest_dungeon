/*
** EPITECH PROJECT, 2024
** B-MUL-200-PAR-2-1-myrpg-pierre.pruvost
** File description:
** load_save.c
*/

#include "game.h"
#include "my.h"
#include <fcntl.h>
#include <string.h>

static void setup_malloc_entity(entity_t *player)
{
    player->display[EXPLO_STATE] = malloc(sizeof(sprite_t));
    player->display[COMBAT_STATE] = malloc(sizeof(sprite_t));
    player->squad = malloc(sizeof(entity_t *) * NB_ENTITY_SQUAD);
}

static void set_spells(char *line, entity_t **entity)
{
    char **line_arr = my_str_to_word_arr(line, ';');

    for (int i = 0; line_arr[i] != NULL && i < 4; ++i) {
        (*entity)->capacities[i] = atoi(line_arr[i]);
    }
    free_arr(line_arr);
}

static void get_name(char *line, entity_t **entity)
{
    int i = 0;

    for (i; i < strlen(line) && line[i] != '\0'; ++i) {
        (*entity)->name[i] = line[i];
    }
    (*entity)->name[i] = '\0';
}

static void set_info_entity(entity_t *player, int id)
{
    char **file = get_file_as_arr(ENTITY_INFO_FILEPATH[id]);

    for (int i = 0; file[i] != NULL; ++i) {
        if (strcmp(file[i], NAME_ENT) == 0 && file[i + 1] != NULL)
            get_name(file[i + 1], &player);
        if (strcmp(file[i], CAPA_ENT) == 0 && file[i + 1] != NULL)
            set_spells(file[i + 1], &player);
    }
}

static stats_t *set_stats_from_save(stats_t save)
{
    stats_t *stats = malloc(sizeof(stats_t));

    stats->atk = save.atk;
    stats->hp = save.hp;
    stats->spd = save.spd;
    stats->pro = save.pro;
    stats->pre = save.pre;
    stats->crt = save.crt;
    return stats;
}

static void set_explo_info(entity_t *player, save_entity_t save)
{
    player->pos[0] = save.pos.x, 
    player->pos[1] = save.pos.y;
    player->rect = (sfIntRect){0, 0, 32, 32};
    player->status = 0;
}

static entity_t *set_player_from_save(save_entity_t save_entity)
{
    entity_t *player = malloc(sizeof(entity_t));

    setup_malloc_entity(player);
    player->id = save_entity.player_id;
    set_entity_sprite_combat(player, player->id);
    set_entity_sprite_explo(player, player->id);
    set_explo_info(player, save_entity);
    set_info_entity(player, player->id);
    player->level = save_entity.level;
    player->xp = save_entity.xp;
    player->stats = set_stats_from_save(save_entity.stats);
    player->mod = set_stats_from_save(save_entity.mod);
    for (int i = 0; i < 3; ++i)
        player->items[i] = save_entity.items[i];
    player->orientation = LEFT;
    player->movement = LEFT;
    player->clock = sfClock_create();
    return player;
}

static void set_player_squad_from_save(save_entity_t squad[],
    entity_t *player)
{
    for (int i = 0; i < NB_ENTITY_SQUAD; ++i) {
        if (squad[i].player_id == -1)
            player->squad[i] = NULL;
        else
            player->squad[i] = set_player_from_save(squad[i]);
    }
}

sfBool set_save_from_file(display_t *display)
{
    int fd = 0;
    saves_t save = {0};
    entity_t *player = NULL;
    dungeon_t *dungeon = NULL;

    return sfTrue;
    logs(INFO, "Loading game from file...");
    fd = open(SAVE_FOLDER, O_RDONLY);
    if (fd != -1) {
        read(fd, &save, sizeof(saves_t));
        logs(INFO, "File readed..");
    } else {
        logs(ERROR, "Could not open the save file");
        return sfTrue;
    }
    player = set_player_from_save(save.player);
    set_player_squad_from_save(save.squad, player);
    for (int i = 0; i < INVENTORY_SIZE; ++i)
        player->inventory[i] = save.inventory[i];
    logs(SUCCESS, "File loaded, launching game...");
    dungeon = setup_dungeon(player);
    if (game(display, player, dungeon) == 84)
        return sfFalse;
    return sfTrue;
}
