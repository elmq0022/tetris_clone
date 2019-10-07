#include <stdio.h>
#include <allegro5/allegro_primitives.h>

#include "load_game_env.h"
#include "draw_board.h"
#include "board.h"
#include "pieces.h"


int main(){

    env game_env = load_game_env(); 

    bool redraw = true;
    bool done = false;

    ALLEGRO_EVENT event;

    board b = board_initialize();

    al_start_timer(game_env.timer);
    while(true){
        al_wait_for_event(game_env.queue, &event);
        
        switch(event.type){

            case ALLEGRO_EVENT_TIMER:
                // move piece down every x seconds
                if(al_get_timer_count(game_env.timer) % 15 == 0){
                   if(!(board_move_piece(&b, 0, DOWN))){
                       board_set_piece(&b);
                       board_find_full_rows(&b);
                       board_clear_full_rows(&b);
                       board_move_full_rows(&b);
                       board_update_score_and_level(&b);
                   }
                }
                redraw = true;
                break;

            case ALLEGRO_EVENT_KEY_DOWN:
                if(event.keyboard.keycode == ALLEGRO_KEY_LEFT){
                    board_move_piece(&b, LEFT, 0);
                }
                else if(event.keyboard.keycode == ALLEGRO_KEY_RIGHT){
                    board_move_piece(&b, RIGHT, 0);
                }
                else if(event.keyboard.keycode == ALLEGRO_KEY_UP){
                    board_rotate_piece(&b, COUNTER_CLOCK_WISE);
                }
                else if(event.keyboard.keycode == ALLEGRO_KEY_DOWN){
                    board_rotate_piece(&b, CLOCK_WISE);
                }
                break;

            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                done = true;
                break;
        } 

        if(done){
            break;
        }

        if(redraw && al_event_queue_is_empty(game_env.queue)){
            al_clear_to_color(al_map_rgb(0, 0, 0));
            draw_board(&game_env, &b); 
            al_flip_display();
            redraw = false;
        }
    }
    
    unload_game_env(game_env);
    board_destroy(b);

    return 0;
}
