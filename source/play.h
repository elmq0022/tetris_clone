#ifndef PLAY_H
#define PLAY_H

#include <allegro5/allegro5.h>
#include "load_game_env.h"
#include "board.h"
#include "draw_board.h"

void play_update(env* _env);
void play_draw(env* _env);

#endif
