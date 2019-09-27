#include <stdio.h>

#include "board.h"
#include "pieces.h"

#include <allegro5/allegro5.h>

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
    ALLEGRO_EVENT e;

    al_start_timer(timer);
    while(true){
        al_wait_for_event(queue, &e);
        if(e.type == ALLEGRO_EVENT_TIMER){
            redraw = true;
        }

        else if ((e.type == ALLEGRO_EVENT_KEY_DOWN) || (e.type == ALLEGRO_EVENT_DISPLAY_CLOSE)){
            break;
        }

        if(redraw && al_event_queue_is_empty(queue)){
            al_clear_to_color(al_map_rgb(0, 0, 0));
            al_flip_display();
        }
    } 

    al_destroy_display(display);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);

    return 0;
}
