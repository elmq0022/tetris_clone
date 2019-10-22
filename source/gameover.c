#include "board.h"
#include "load_game_env.h"
#include <allegro5/allegro_primitives.h>

void update_gameover(env* _env){
    if(_env->key[ALLEGRO_KEY_ENTER]){
        _env->active_state = HIGH_SCORE;
        //most definitely creating a leak here...
        // CLEAN IT UP
        // TODO: FIX THIS
        //board b = board_initialize();
        //_env->b = &b;
        memset(_env->key, 0, sizeof(_env->key));
    }
}

void draw_gameover(env* _env){
    al_draw_textf(
        _env->font,
        al_map_rgb(255, 255, 255),
        D_WIDHT/2, D_HEIGHT/2,
        ALLEGRO_ALIGN_CENTER,
        "%s",
        "GAME OVER"
    );
    
    al_draw_multiline_text(
            _env->font,
            al_map_rgb(255, 255, 255),
            10,
            D_HEIGHT - 30,
            D_WIDHT - 10,
            10,
            ALLEGRO_ALIGN_LEFT,
            "Press ENTER to return to CONTINUE"
    );
}
