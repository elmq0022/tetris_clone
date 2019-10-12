#include <allegro5/allegro5.h>
#include "load_game_env.h"
#include "board.h"
#include "draw_board.h"


void play_update(env* _env){
    switch(_env->event.type){

        case ALLEGRO_EVENT_TIMER:
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
            _env->redraw = true;
            break;

        case ALLEGRO_EVENT_KEY_DOWN:
            if(_env->event.keyboard.keycode == ALLEGRO_KEY_LEFT){
                board_move_piece(_env->b, LEFT, 0);
            }
            else if(_env->event.keyboard.keycode == ALLEGRO_KEY_RIGHT){
                board_move_piece(_env->b, RIGHT, 0);
            }
            else if(_env->event.keyboard.keycode == ALLEGRO_KEY_UP){
                board_rotate_piece(_env->b, COUNTER_CLOCK_WISE);
            }
            else if(_env->event.keyboard.keycode == ALLEGRO_KEY_DOWN){
                board_rotate_piece(_env->b, CLOCK_WISE);
            }
            else if(_env->event.keyboard.keycode == ALLEGRO_KEY_SPACE){
                while(board_move_piece(_env->b, 0, DOWN)){
                    //drop the piece
                }
            }

            break;

        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            _env->done = true;
            break;
    } 

}

void play_draw(env* _env){
    draw_board(_env); 
}
