#include "load_game_env.h"

void update_start_screen(env* _env){
    // TODO: define start screen logic
    if(_env->key[ALLEGRO_KEY_ENTER]){
        _env->active_state = PLAY;
    }
    if(_env->key[ALLEGRO_KEY_SPACE]){
        _env->active_state = HIGH_SCORE;
        memset(_env->key, 0, sizeof(_env->key));
    }
}

void draw_start_screen(env* _env){
    // TODO: define start screen drawing routines
    al_draw_multiline_text(
            _env->font,
            al_map_rgb(255, 255, 255),
            D_WIDHT/2,
            D_HEIGHT/2,
            D_WIDHT-10,
            10,
            ALLEGRO_ALIGN_CENTER,
            "Welcome to TETROMINOES\n"
            "Press ENTER to PLAY\n"
            "Press SPACE-BAR for the HIGH SCORES"
    );
}
