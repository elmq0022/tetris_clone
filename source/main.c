#include <stdio.h>

#include "board.h"
#include "pieces.h"

#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>

#define D_WIDHT 320
#define D_HEIGHT 200
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

    al_start_timer(timer);
    while(true){
        al_wait_for_event(queue, &e);
        
        switch(e.type){

            case ALLEGRO_EVENT_TIMER:
                if(al_get_timer_count(timer) % 300 == 0){
                    printf("five seconds have passed\n");
                }
                redraw = true;
                break;

            case ALLEGRO_EVENT_KEY_DOWN:
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                done = true;
                break;
        } 

        if(done){
            break;
        }

        if(redraw && al_event_queue_is_empty(queue)){
            al_clear_to_color(al_map_rgb(0, 0, 0));
            // TODO: draw the board to the screen
            // TODO: draw the piece to the screen
            for(int i=PADDING; i<NUM_COLUMNS-PADDING; i++){
                for(int j=PADDING; j<NUM_ROWS-PADDING; j++){
                    al_draw_filled_rectangle(10*i, 10*j, 10*(i+1), 10*(j+1), al_map_rgb(255, 0, 0));
                    al_draw_filled_rectangle(10*i+2, 10*j+2, 10*(i+1)-2, 10*(j+1)-2, al_map_rgb(255, 0, 255));
                }
            }

            al_flip_display();
            redraw = false;
        }
    }

    al_destroy_display(display);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);

    return 0;
}
