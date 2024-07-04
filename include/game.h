/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** game.h
*/

#ifndef GAME_H_
    #define GAME_H_

    #include "sprites.h"
    #include "statics.h"
    #include "entity.h"
    #include "maps.h"
    #include "sound.h"

//Window default background color
static const sfColor BG_DEFAULT_COLOR = {24, 19, 38, 255};

////////// STRUCTURE //////////

typedef struct display_s {
    sfRenderWindow *window;
    sprite_t *tab;
    sfMusic **sounds;
    sfVector2f resolution;
} display_t;

//game
bool end_of_game(entity_t *player, dungeon_t *dungeon, int run_game);
int lobby_loop(display_t *display);
int game(display_t *display, entity_t *entity, dungeon_t *dungeon);
void manage_pnj(dungeon_t *d, entity_t *p, display_t *display, int *run_game);
display_t *setup_display(sfRenderWindow *window);
int game_launcher(void);
void display_death_player(display_t *display, entity_t *player,
    int player_pos);
void destroy_dungeon(dungeon_t *dungeon);

//display
void main_display(dungeon_t *dungeon, entity_t *player, display_t *display);
void display_map(display_t *display, dungeon_t *dungeon);
void animation_map_assets(dungeon_t *dungeon);

//events
void move_key(entity_t *player, display_t *display, dungeon_t *dungeon);
void event_listener(display_t *display, entity_t *entity, dungeon_t *dungeon,
    int *run_game);
void manage_heal(dungeon_t *dungeon, entity_t *player, display_t *display);
void manage_chest(dungeon_t *dungeon, entity_t *player, display_t *display);
void get_an_item(display_t *display, entity_t *player, int chance);
void chest_opening(display_t *display, int item);
void anim_chest_opening(display_t *display, sfText *text, int item);
void display_chest_obtained(display_t *display, sfText *text, int item);
void manage_boss(dungeon_t *dungeon, entity_t *player,
    display_t *display, int *run_game);

//menus
void pause_menu(display_t *display, int *run_game);
void options(display_t *display, sprite_t *sprites);
void inventory(display_t *display, entity_t *player);
void display_inventory(display_t *display, entity_t *player, sfText *text,
    int *selection);
void display_part_stats(display_t *display, sfText *text, stats_t stats,
    sfVector2f pos);
int chose_stat(display_t *display, entity_t *player, entity_t *upgrading);
int hero_selection(display_t *display, sprite_t *sprites);
int is_in_hitbox_menu(sfVector2i pos, int index);
sfIntRect get_rect_menu(int index, int offset);
void help_popup(display_t *display, sprite_t *sprites);

//utils
sfText *init_text(sfFont *font, sfVector2f pos, sfColor color, int size);
int is_in_hitbox(sfVector2i pos, int index);
sfVector2f combine_vectors(sfVector2f vect1, sfVector2f vect2);
int is_in_zone(sfVector2i pos, sfVector2f zone, sfVector2f zone_size);


void level_up_entity(entity_t *entity, display_t *display,
    int identity, int lvl_gain);

////////////// SAVES //////////////
    #define SAVE_FOLDER "src/menus/saves/.game_saves/"
    #define MAX_SAVE 5

typedef struct save_entity_s {
    int player_id;
    sfVector2f pos;
    int level;
    int xp;
    stats_t stats;
    stats_t mod;
    int items[3];
} save_entity_t;

typedef struct save_dungeon_s {
    int floor;
    sfVector2i co_map;
    maps_t maps[SIZE_DUNGEON][SIZE_DUNGEON];
} save_dungeon_t;

typedef struct saves_s {
    save_entity_t player;
    int inventory[INVENTORY_SIZE];
    save_entity_t squad[NB_ENTITY_SQUAD];
    //save_dungeon_t dungeon;
} saves_t;

sfBool set_save_from_file(display_t *display);
int save_game_in_file(dungeon_t *dungeon, entity_t *player);

#endif
