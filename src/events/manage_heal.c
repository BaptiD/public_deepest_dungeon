/*
** EPITECH PROJECT, 2024
** pnj
** File description:
** functions to manage space heal stations
*/

#include <stdio.h>
#include <stdbool.h>

#include "game.h"
#include "combat.h"
#include "my.h"

sfBool next_to_heal(dungeon_t *dungeon, entity_t *player, int x, int y)
{
    if (player->pos[1] + y >= 0 && player->pos[1] + y <= 19 &&
        player->pos[0] + x >= 0 && player->pos[0] + x <= 19) {
        if (ACTUAL_MAP.char_map[player->pos[1] + y][player->pos[0] + x]
            == MAP_HEAL) {
            ACTUAL_MAP.char_map[player->pos[1] + y][player->pos[0] + x] = ' ';
            return sfTrue;
        }
    }
    return sfFalse;
}

sfBool is_close_to_heal(dungeon_t *dungeon, entity_t *player)
{
    if (next_to_heal(dungeon, player, -1, -1) == sfTrue)
        return sfTrue;
    if (next_to_heal(dungeon, player, -1, 0) == sfTrue)
        return sfTrue;
    if (next_to_heal(dungeon, player, -1, 1) == sfTrue)
        return sfTrue;
    if (next_to_heal(dungeon, player, 0, -1) == sfTrue)
        return sfTrue;
    if (next_to_heal(dungeon, player, 0, 1) == sfTrue)
        return sfTrue;
    if (next_to_heal(dungeon, player, 1, -1) == sfTrue)
        return sfTrue;
    if (next_to_heal(dungeon, player, 1, 0) == sfTrue)
        return sfTrue;
    if (next_to_heal(dungeon, player, 1, 1) == sfTrue)
        return sfTrue;
    return sfFalse;
}

static void check_max(entity_t *player)
{
    if (player->mod->hp > 0)
        player->mod->hp = 0;
}

static void heal_main_player(entity_t *player)
{
    int max_heal = 0;

    for (int i = 0; i < 4; i++) {
        if (player->squad[i] != NULL) {
            max_heal = player->squad[i]->stats->hp / 2;
            player->squad[i]->mod->hp += max_heal;
            check_max(player->squad[i]);
        }
    }
}

static int get_event(display_t *display)
{
    sfEvent event;

    while (sfRenderWindow_pollEvent(display->window, &event)) {
        if (event.type == sfEvtClosed)
            sfRenderWindow_close(display->window);
        if (event.type == sfEvtKeyPressed)
            return 1;
    }
    return 0;
}

void display_heal(dungeon_t *dungeon, entity_t *player, display_t *display)
{
    int continu = 0;
    sfText *text = sfText_create();
    sfFont *font = sfFont_createFromFile(FONT);

    sfText_setPosition(text,
    (sfVector2f){get_random_nb(800, 1000), get_random_nb(400, 600)});
    sfText_setFont(text, font);
    sfText_setColor(text, sfGreen);
    sfText_setCharacterSize(text, 40);
    sfText_setString(text, "Healed!");
    while (sfRenderWindow_isOpen(display->window) && continu == 0) {
        continu = get_event(display);
        display_map(display, dungeon);
        player->rect = display_entity(display->window, player->clock,
        player->display[EXPLO_STATE], player->rect);
        sfRenderWindow_drawText(display->window, text, NULL);
        sfRenderWindow_display(display->window);
        sfRenderWindow_clear(display->window, BG_DEFAULT_COLOR);
    }
}

void manage_heal(dungeon_t *dungeon, entity_t *player, display_t *display)
{
    if (sfKeyboard_isKeyPressed(sfKeyE) == sfTrue) {
        if (is_close_to_heal(dungeon, player) == sfTrue) {
            heal_main_player(player);
            get_sprite_map(dungeon, player);
            display_heal(dungeon, player, display);
        }
    }
}
