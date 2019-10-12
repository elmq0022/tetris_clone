#include "board.h"
#include "load_game_env.h"
#include <allegro5/allegro_primitives.h>

void update_gameover(env* _env){
    switch(_env->event.type){
        case ALLEGRO_EVENT_TIMER:
            _env->redraw = true;
            break;
        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            _env->done = true;
            break;
    }
}

void draw_gameover(env* _env){
    al_draw_textf(_env->font, al_map_rgb(255, 255, 255), D_WIDHT/2, D_HEIGHT/2, ALLEGRO_ALIGN_CENTER, "%s", "GAME OVER");
}
