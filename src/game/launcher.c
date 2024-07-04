/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** game_loop/launcher.c
*/

#include "game.h"
#include "sprites.h"
#include "statics.h"
#include "my.h"
#include "menus.h"

static void display_loading_border(sfRenderWindow *window)
{
    sfSprite *sprite = sfSprite_create();
    sfTexture *texture = sfTexture_createFromFile(
        "assets/combat/HP_bar1.png", NULL);

    sfSprite_setTexture(sprite, texture, sfTrue);
    sfSprite_setPosition(sprite,
        (sfVector2f){LOAD_BAR_POS.x + 640, LOAD_BAR_POS.y});
    sfSprite_setRotation(sprite, 90);
    sfSprite_setScale(sprite, RESIZE_LOAD_BORDER);
    sfRenderWindow_drawSprite(window, sprite, NULL);
    sfSprite_destroy(sprite);
    sfTexture_destroy(texture);
}

static void display_loading_bar(sfRenderWindow *window, int number)
{
    sfSprite *sprite = sfSprite_create();
    sfTexture *texture = sfTexture_createFromFile(
        "assets/menus/loading/load_bar.png", NULL);

    sfSprite_setTexture(sprite, texture, sfTrue);
    sfSprite_setPosition(sprite, (sfVector2f){LOAD_BAR_POS.x + LOAD_BAR_OFST.x,
        LOAD_BAR_POS.y + LOAD_BAR_OFST.y});
    sfSprite_setScale(sprite, LOAD_BAR_SIZES[number]);
    sfRenderWindow_drawSprite(window, sprite, NULL);
    display_loading_border(window);
    sfSprite_destroy(sprite);
    sfTexture_destroy(texture);
}

void display_loading(sfRenderWindow *window, int number)
{
    sfSprite *sprite = sfSprite_create();
    sfTexture *t = sfTexture_createFromFile(
        "assets/menus/loading/loading.png", NULL);
    int sizex = VIDEOMODE.width / 2 - (680 / 2);
    int sizey = VIDEOMODE.height / 2 - (200 / 2);
    sfVector2f pos = (sfVector2f){sizex, sizey};

    sfRenderWindow_clear(window, sfWhite);
    sfSprite_setTexture(sprite, t, sfTrue);
    sfSprite_setPosition(sprite, pos);
    sfRenderWindow_drawSprite(window, sprite, NULL);
    display_loading_bar(window, number);
    sfRenderWindow_display(window);
    sfSprite_destroy(sprite);
    sfTexture_destroy(t);
}

static void destroy_game(display_t *display)
{
    logs(INFO, "Destroying game entities...");
    logs(INFO, "Starting sprites destruction...");
    destroy_sprites(display->tab, SIZE_TAB);
    free_sounds(display->sounds);
    logs(SUCCESS, "All sprites destructed");
    logs(INFO, "Destroying game window...");
    sfRenderWindow_destroy(display->window);
    logs(SUCCESS, "Game window destroyed");
    logs(SUCCESS, "Player entity destroyed");
    logs(SUCCESS, "All game entities destroyed");
}

int game_launcher(void)
{
    int status = 0;
    sfRenderWindow* window = NULL;
    display_t *display = NULL;

    logs(INFO, "Launching game entities...");
    window = sfRenderWindow_create(VIDEOMODE, GAME_NAME, sfResize | sfClose,
        NULL);
    if (!window)
        return 84;
    sfRenderWindow_setFramerateLimit(window, FPS);
    display_loading(window, 0);
    display = setup_display(window);
    display_loading(window, 1);
    play_sound(display->sounds[BG_MUSIC_WAV]);
    display_loading(window, 2);
    sfMusic_setLoop(display->sounds[BG_MUSIC_WAV], sfTrue);
    display_loading(window, 3);
    status = lobby_loop(display);
    destroy_game(display);
    return status;
}
