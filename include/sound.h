/*
** EPITECH PROJECT, 2024
** B-MUL-200-PAR-2-1-myrpg-pierre.pruvost
** File description:
** sound.h
*/

#ifndef SOUND_H_
    #define SOUND_H_
    #include <SFML/Audio.h>

enum sounds {
    BG_MUSIC_WAV,
    COMBAT_MUSIC_WAV,
    WRONG_WAV,
    HOVER_WAV,
    ATK_1_WAV,
    ATK_2_WAV,
    BUFF_WAV,
    DEBUFF_WAV,
    HEAL_WAV,
    MISS_WAV,
    DROP_WAV,
    START_WAV,
    CLICK_WAV,
    CHEST_WAV,
    STUN_WAV,
    BLEED_WAV,
    BURN_WAV,
    POISON_WAV,
    KEY_PRESS_WAV
};

//Sounds paths
static const char *SOUND_PATH[] = {
    "assets/sound/bg_music.wav",
    "assets/sound/combat/combat_music.wav",
    "assets/sound/wrong.wav",
    "assets/sound/hover.wav",
    "assets/sound/combat/attack_1.wav",
    "assets/sound/combat/attack_2.wav",
    "assets/sound/combat/buff.wav",
    "assets/sound/combat/debuff.wav",
    "assets/sound/combat/heal.wav",
    "assets/sound/combat/miss.wav",
    "assets/sound/menus/hover.wav",
    "assets/sound/menus/start.wav",
    "assets/sound/menus/click.wav",
    "assets/sound/menus/chest_open.wav",
    "assets/sound/combat/bleed.wav",
    "assets/sound/combat/bleed.wav",
    "assets/sound/combat/burn.wav",
    "assets/sound/combat/poison.wav",
    "assets/sound/key_pressed.wav",
};

static const double SOUND_VOLUME[] = {
    15.0,
    15.0,
    30.0,
    30.0,
    30.0,
    30.0,
    30.0,
    30.0,
    30.0,
    30.0,
    3.0,
    15.0,
    15.0,
    30.0,
    30.0,
    20.0,
    70.0,
    35.0,
    20.0
};

static const int NB_SOUNDS = sizeof(SOUND_PATH) / sizeof(char *);

////////// FUNCTIONS ///////////

sfMusic **init_sounds_array(void);
void play_sound(sfMusic *sound);
void free_sounds(sfMusic **arr);

#endif
