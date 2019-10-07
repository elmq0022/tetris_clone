#include <stdio.h>
#include <allegro5/allegro_primitives.h>

#include "load_game_env.h"
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

            // draw the board to the screen
            for(int y=PADDING; y<NUM_ROWS-PADDING; y++){ 
                for(int x=PADDING; x<NUM_COLUMNS-PADDING; x++){
                    if(b.rows[y]->cells[x]){
                        al_draw_filled_rectangle(
                            10*x,
                            10*y,
                            10*(x+1),
                            10*(y+1),
                            al_map_rgb(255, 0, 0)
                        );
                        //al_draw_filled_rectangle(10*x+2, 10*y+2, 10*(x+1)-2, 10*(y+1)-2, al_map_rgb(255, 0, 255));
                    }
                }
            }

            // draw the piece to the screen
            for(int y=0; y<SIZE; y++){
                for(int x=0; x<SIZE; x++){
                    if(b.pieces[b.piece].rotations[b.rotation][y][x]){
                        al_draw_filled_rectangle(
                            10*(x+b.x),
                            10*(y+b.y),
                            10*(x+b.x+1), 
                            10*(y+b.y+1), 
                            al_map_rgb(255, 0, 0)

                        );
                    }
                }
            }

            // draw the next piece to the screen
            for(int y=0; y<SIZE; y++){
                for(int x=0; x<SIZE; x++){
                    if(b.pieces[b.next_piece].rotations[0][y][x]){
                        al_draw_filled_rectangle(
                            10*(x) + 200,
                            10*(y) + 25,
                            10*(x+1) + 200, 
                            10*(y+1) + 25, 
                            al_map_rgb(255, 0, 0)
                        );
                    }
                }
            }

            // draw the score and the level to the screen
            al_draw_textf(game_env.font, al_map_rgb(255, 255, 255), 200, 100, 0, "SCORE: %d", b.score);
            al_draw_textf(game_env.font, al_map_rgb(255, 255, 255), 200, 125, 0, "LEVEL: %d", b.level);
            
            al_flip_display();
            redraw = false;
        }
    }
    
    unload_game_env(game_env);
    board_destroy(b);

    return 0;
}
