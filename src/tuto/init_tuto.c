/*
** EPITECH PROJECT, 2024
** init_tuto
** File description:
** functions to initialise the tuto
*/

#include "game.h"
#include "maps.h"
#include "entity.h"
#include "tuto.h"

sprite_t *init_popup(void)
{
    sprite_t *popup = malloc(sizeof(sprite_t));

    popup->sprite = sfSprite_create();
    popup->texture = sfTexture_createFromFile("assets/popup_tuto.png", NULL);
    sfSprite_setTexture(popup->sprite, popup->texture, sfTrue);
    sfSprite_setPosition(popup->sprite, (sfVector2f){100, 100});
    sfSprite_setScale(popup->sprite, (sfVector2f){0.8, 0.8});
    return popup;
}

dungeon_t *init_tuto(entity_t *player)
{
    dungeon_t *dungeon = setup_dungeon(player);

    add_pnj(dungeon->pnjs, 1, 0);
    dungeon->pnjs[0]->pos[0] = 18;
    dungeon->pnjs[0]->pos[1] = 10;
    pars_pnj_file(dungeon->pnjs[0], ID_TUTO_PNJ_FILE);
    sfText_setString(dungeon->pnjs[0]->text[NAME]->text,
        dungeon->pnjs[0]->name);
    dungeon->co_map = (sfVector2i){0, 0};
    dungeon->maps[0][0].char_map = get_map_from_file(MAP_TUTO_ID);
    get_sprite_map(dungeon, player);
    return dungeon;
}
