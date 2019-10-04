#include <stdio.h>

#include "board.h"
#include "pieces.h"

#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>

#define D_WIDHT 320
#define D_HEIGHT 400
#define FPS 60


int main(){
    if(!al_init()){
        printf("failed to initialize allegro");
    }

    if(!al_install_keyboard()){
        printf("failed to initialize keyboard");
    }

    if(!al_init_primitives_addon()){
        printf("failed to initialize primatives addon\n");
    }

    ALLEGRO_TIMER* timer;
    if(!(timer=al_create_timer(1.0/FPS))){
        printf("failed to create timer");
    }

    ALLEGRO_EVENT_QUEUE* queue;
    if(!(queue=al_create_event_queue())){
        printf("failed to create event queue");
    }

    ALLEGRO_DISPLAY* display;
    if(!(display=al_create_display(D_WIDHT, D_HEIGHT))){
        printf("failed to create display");
    }

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    bool redraw = true;
    bool done = false;

    ALLEGRO_EVENT e;

    board b = board_initialize();

    al_start_timer(timer);
    while(true){
        al_wait_for_event(queue, &e);
        
        switch(e.type){

            case ALLEGRO_EVENT_TIMER:
                // move piece down every x seconds
                if(al_get_timer_count(timer) % 15 == 0){
                   if(!(board_move_piece(&b, 0, DOWN))){
                       board_set_piece(&b);
                       board_find_full_rows(&b);
                       board_clear_full_rows(&b);
                       board_move_full_rows(&b);
                   }
                }
                redraw = true;
                break;

            case ALLEGRO_EVENT_KEY_DOWN:
                if(e.keyboard.keycode == ALLEGRO_KEY_LEFT){
                    board_move_piece(&b, LEFT, 0);
                }
                else if(e.keyboard.keycode == ALLEGRO_KEY_RIGHT){
                    board_move_piece(&b, RIGHT, 0);
                }
                else if(e.keyboard.keycode == ALLEGRO_KEY_UP){
                    board_rotate_piece(&b, COUNTER_CLOCK_WISE);
                }
                else if(e.keyboard.keycode == ALLEGRO_KEY_DOWN){
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

        if(redraw && al_event_queue_is_empty(queue)){
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

            al_flip_display();
            redraw = false;
        }
    }
    
    board_destroy(b);
    al_destroy_display(display);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);

    return 0;
}
