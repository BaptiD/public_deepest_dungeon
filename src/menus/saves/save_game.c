/*
** EPITECH PROJECT, 2024
** B-MUL-200-PAR-2-1-myrpg-pierre.pruvost
** File description:
** save_game.c
*/

#include "game.h"
#include "my.h"
#include <stdio.h>
#include <time.h>

static save_dungeon_t save_dungeon_in_struct(dungeon_t *dungeon)
{
    save_dungeon_t save = {0};

    save.floor = dungeon->floor;
    save.co_map = dungeon->co_map;
    for (int i = 0; i < SIZE_DUNGEON; ++i) {
        //save.maps[i] = dungeon->maps[i];
    }
    return save;
}

static saves_t save_inventory_in_struct(int inventory[], saves_t save)
{
    for (int i = 0; i < INVENTORY_SIZE; ++i) {
        save.inventory[i] = inventory[i];
    }
    logs(SUCCESS, "Inventory saved OK");
    return save;
}

static stats_t get_stats(stats_t *entity_stats)
{
    stats_t save = {0};

    save.atk = entity_stats->atk;
    save.hp = entity_stats->hp;
    save.spd = entity_stats->spd;
    save.pro = entity_stats->pro;
    save.pre = entity_stats->pre;
    save.crt = entity_stats->crt;
    return save;
}

static save_entity_t save_player_in_struct(entity_t *entity)
{
    save_entity_t save;

    save.player_id = entity->id;
    save.pos = (sfVector2f){entity->pos[0], entity->pos[1]};
    save.level = entity->level;
    save.xp = entity->xp;
    save.stats = get_stats(entity->stats);
    save.mod = get_stats(entity->mod);
    for (int i = 0; i < 3; ++i)
        save.items[i] = entity->items[i];
    logs(SUCCESS, "Player saved OK");
    return save;
}

static saves_t save_squad_in_struct(entity_t **squad, saves_t save)
{
    for (int i = 0; i < NB_ENTITY_SQUAD; ++i) {
        if (squad[i] != NULL)
            save.squad[i] = save_player_in_struct(squad[i]);
        else
            save.squad[i].player_id = -1;
    }
    logs(SUCCESS, "Squad saved OK");
    return save;
}

static char *set_filepath_save(int save_id)
{
    char date[100];
    time_t time_save = time(NULL);
    char *filepath = NULL;

    strftime(date, sizeof(date), "%d-%m-%y_%X", localtime(&time_save));
    filepath = malloc(sizeof(date) + sizeof(SAVE_FOLDER) + 9);
    sprintf(filepath, "%sDD%d_%s.save", SAVE_FOLDER, save_id, date);
    return filepath;
}

int save_game_in_file(dungeon_t *dungeon, entity_t *player)
{
    FILE *stream = 0;
    saves_t save = {0};
    char *filepath = set_filepath_save(1);

    logs(INFO, "Saving game in file...");
    save.player = save_player_in_struct(player);
    save = save_inventory_in_struct(player->inventory, save);
    save = save_squad_in_struct(player->squad, save);
    stream = fopen(filepath, "w");
    if (stream != NULL) {
        fwrite(&save, sizeof(saves_t), 1, stream);
        logs(INFO, "File written...");
    } else {
        fclose(stream);
        logs(ERROR, "Could not save the game");
        return 84;
    }
    logs(SUCCESS, "Game saved OK");
    free(filepath);
    fclose(stream);
    return 0;
}
