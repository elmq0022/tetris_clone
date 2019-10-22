#include "load_game_env.h"

void update_high_score(env* _env){
    if(_env->key[ALLEGRO_KEY_ENTER]){
        _env->active_state = START_SCREEN;
        memset(_env->key, 0, sizeof(_env->key));
    }
    if(_env->key[ALLEGRO_KEY_SPACE]){
        _env->active_state = PLAY;
        memset(_env->key, 0, sizeof(_env->key));
    }
}

void draw_high_score(env* _env){

    for(int i=0; i<10; i++){
        al_draw_textf(
            _env->font,
            al_map_rgb(255, 255, 255),
            20,
            10*(i+1),
            0,
            "%d: %d",
            i, _env->high_scores[i]
        );
    } 

    al_draw_multiline_text(
            _env->font,
            al_map_rgb(255, 255, 255),
            10,
            D_HEIGHT - 30,
            D_WIDHT - 10,
            10,
            ALLEGRO_ALIGN_LEFT,
            "Press ENTER to return to START SCREEN\n"
            "Press SPACE BAR to start a new GAME"
    );
}
