#ifndef LOAD_GAME_ENV_H
#define LOAD_GAME_ENV_H

#include <stdio.h>

#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>

#include "board.h"
#include "high_score.h"

#define D_WIDHT 320
#define D_HEIGHT 400
#define FPS 60

#define KEY_SEEN 1
#define KEY_RELEASED 2

typedef enum {
    START_SCREEN,
    PLAY,
    GAMEOVER,
    HIGH_SCORE
} states;

typedef struct {
    ALLEGRO_TIMER* timer;
    ALLEGRO_EVENT_QUEUE* queue;
    ALLEGRO_EVENT event;
    ALLEGRO_DISPLAY* display;
    ALLEGRO_FONT* font;
    states active_state;
    bool done;
    bool redraw;
    board* b;
    unsigned char key[ALLEGRO_KEY_MAX];
    int high_scores[NUM_HIGH_SCORES];
} env;

env load_game_env();
void unload_game_env(env* e);

#endif
