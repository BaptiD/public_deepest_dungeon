/*
** EPITECH PROJECT, 2024
** init_pnjs
** File description:
** init pnjs from file
*/

#include <fcntl.h>
#include <sys/stat.h>

#include "entity.h"
#include "statics.h"
#include "my.h"
#include "combat.h"

void set_pnj_sprite_explo(pnj_t *pnj, int pnj_enum)
{
    pnj->display[EXPLO_STATE] = malloc(sizeof(sprite_t));
    pnj->display[EXPLO_STATE]->sprite = sfSprite_create();
    pnj->display[EXPLO_STATE]->texture = sfTexture_createFromFile(
        ENTITY_EXPLO_SPRITE_FILEPATH[ID_PNJ_SPRITE], NULL);
    pnj->rect = (sfIntRect){0, 0, 32, 32};
    sfSprite_setTexture(pnj->display[EXPLO_STATE]->sprite,
        pnj->display[EXPLO_STATE]->texture, sfTrue);
    sfSprite_setPosition(pnj->display[EXPLO_STATE]->sprite, (sfVector2f){
        MAP_VISIBLE_X / 2, MAP_VISIBLE_Y / 2});
    sfSprite_setTextureRect(pnj->display[EXPLO_STATE]->sprite,
        pnj->rect);
    sfSprite_setScale(pnj->display[EXPLO_STATE]->sprite,
        (sfVector2f){MAP_SQUARE / 32, MAP_SQUARE / 32});
    pnj->clock = sfClock_create();
}

void set_pnj_sprite_combat(pnj_t *pnj, int pnj_enum)
{
    pnj->display[COMBAT_STATE] = malloc(sizeof(sprite_t));
    pnj->display[COMBAT_STATE]->sprite = sfSprite_create();
    pnj->display[COMBAT_STATE]->texture = sfTexture_createFromFile(
        COMBAT_ANIMATION[pnj_enum][IDLE].path, NULL);
    sfSprite_setTexture(pnj->display[COMBAT_STATE]->sprite,
        pnj->display[COMBAT_STATE]->texture, sfTrue);
    sfSprite_setTextureRect(pnj->display[COMBAT_STATE]->sprite,
        pnj->rect);
    sfSprite_setScale(pnj->display[COMBAT_STATE]->sprite,
        (sfVector2f){3, 3});
    sfSprite_setPosition(pnj->display[COMBAT_STATE]->sprite,
        (sfVector2f){0, 400});
}

static void pars_info(pnj_t *pnj, char *buff)
{
    char **content = my_str_to_word_arr(buff, ';');
    int len = len_arr(content);

    free(buff);
    pnj->name = my_strdup(content[len - 1]);
    content[len - 1] = NULL;
    pnj->dialogue = content;
}

void pars_pnj_file(pnj_t *pnj, int type)
{
    char *buff;
    struct stat s;
    int fd = open(PNJS_FILE[type], O_RDONLY);

    if (fd == -1 || stat(PNJS_FILE[type], &s) == -1 || s.st_size == 0)
        return;
    buff = malloc(sizeof(char) * (s.st_size + 1));
    if (buff == NULL)
        return;
    if (read(fd, buff, s.st_size) == -1) {
        free(buff);
        return;
    }
    buff[s.st_size] = '\0';
    close(fd);
    pars_info(pnj, buff);
}

static sprite_t *set_sprite_txt(void)
{
    sfVector2f pos = {0, 765};
    sprite_t *display = malloc(sizeof(sprite_t));

    display->sprite = sfSprite_create();
    display->texture = sfTexture_createFromFile("assets/popup.png", NULL);
    sfSprite_setTexture(display->sprite, display->texture, sfTrue);
    sfSprite_setScale(display->sprite, (sfVector2f){0.98, 0.5});
    sfSprite_setPosition(display->sprite, pos);
    return display;
}

static text_t *set_text(void)
{
    text_t *text = malloc(sizeof(text_t));
    sfFont *font = sfFont_createFromFile(FONT);

    text->text = sfText_create();
    sfText_setPosition(text->text, (sfVector2f){100, 830});
    sfText_setFont(text->text, font);
    sfText_setColor(text->text, sfBlack);
    sfText_setCharacterSize(text->text, 50);
    text->sprite = set_sprite_txt();
    return text;
}

static text_t *set_text_name(pnj_t *pnj)
{
    text_t *text = malloc(sizeof(text_t));
    sfFont *font = sfFont_createFromFile(FONT);
    sfVector2f pos = sfSprite_getPosition(pnj->text[DIALOGUE]->sprite->sprite);

    pos.x += 180;
    pos.y += 15;
    text->text = sfText_create();
    sfText_setPosition(text->text, pos);
    sfText_setFont(text->text, font);
    sfText_setColor(text->text, sfBlack);
    sfText_setCharacterSize(text->text, 35);
    sfText_setString(text->text, pnj->name);
    return text;
}

static int get_pnj_type(pnj_t **pnjs, int i, int player_id)
{
    if (i == player_id)
        return i + 1;
    if (i == 0)
        return i;
    return pnjs[i - 1]->type + 1;
}

void add_pnj(pnj_t **pnjs, int i, int player_id)
{
    pnjs[i]->co_room = (sfVector2i){0, 0};
    pnjs[i]->status_quest = NOT_DONE;
    pnjs[i]->dialogue_line = 0;
    pnjs[i]->is_talking = false;
    pnjs[i]->pos[0] = -1;
    pnjs[i]->pos[1] = -1;
    pnjs[i]->rect = (sfIntRect){0, 0, 32, 32};
    pnjs[i]->text[DIALOGUE] = set_text();
    pnjs[i]->type = get_pnj_type(pnjs, i, player_id);
    pnjs[i]->dialogue = NULL;
    pars_pnj_file(pnjs[i], pnjs[i]->type);
    pnjs[i]->text[NAME] = set_text_name(pnjs[i]);
    if (pnjs[i]->dialogue != NULL) {
        pnjs[i]->text[DIALOGUE]->dialogue = pnjs[i]->dialogue[pnjs[i]->dialogue_line];
        sfText_setString(pnjs[i]->text[DIALOGUE]->text, pnjs[i]->text[DIALOGUE]->dialogue);
    }
    set_pnj_sprite_explo(pnjs[i], pnjs[i]->type);
    set_pnj_sprite_combat(pnjs[i], pnjs[i]->type);
}

pnj_t **setup_pnjs(entity_t *player)
{
    pnj_t **pnjs = malloc(sizeof(pnj_t *) * NB_PNJ);

    for (size_t i = 0; i < NB_PNJ; i++) {
        pnjs[i] = malloc(sizeof(pnj_t));
        add_pnj(pnjs, i, player->id);
    }
    return pnjs;
}
