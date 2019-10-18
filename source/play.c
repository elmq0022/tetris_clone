#include <allegro5/allegro5.h>
#include "load_game_env.h"
#include "board.h"
#include "draw_board.h"


void play_update(env* _env){
    // move piece down every x seconds
    if(al_get_timer_count(_env->timer) % 15 == 0){
        if(!(board_move_piece(_env->b, 0, DOWN))){
            if(!board_set_piece(_env->b)){
                _env->active_state = GAMEOVER;
            }
            board_find_full_rows(_env->b);
            board_clear_full_rows(_env->b);
            board_move_full_rows(_env->b);
            board_update_score_and_level(_env->b);
        }
    }

    if(al_get_timer_count(_env->timer) % 5 == 0){
        if(_env->key[ALLEGRO_KEY_LEFT]){
            board_move_piece(_env->b, LEFT, 0);
        }
        if(_env->key[ALLEGRO_KEY_RIGHT]){
            board_move_piece(_env->b, RIGHT, 0);
        }
        if(_env->key[ALLEGRO_KEY_UP]){
            board_rotate_piece(_env->b, COUNTER_CLOCK_WISE);
            _env->key[ALLEGRO_KEY_UP] &= KEY_RELEASED;
        }
        if(_env->key[ALLEGRO_KEY_DOWN]){
            board_rotate_piece(_env->b, CLOCK_WISE);
            _env->key[ALLEGRO_KEY_DOWN] &= KEY_RELEASED;
        }

        if(_env->key[ALLEGRO_KEY_SPACE]){
            while(board_move_piece(_env->b, 0, DOWN)){
                //drop the piece
            }
            _env->key[ALLEGRO_KEY_SPACE] &= KEY_RELEASED; 
        }
    } 
}

void play_draw(env* _env){
    draw_board(_env); 
}
