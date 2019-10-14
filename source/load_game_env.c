#include <stdio.h>

#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>

#include "board.h"

#define D_WIDHT 320
#define D_HEIGHT 400
#define FPS 60

#define KEY_SEEN 1
#define KEY_RELEASED 2

typedef enum {
    START_SCREEN,
    PLAY,
    GAMEOVER
} states;

typedef struct {
    ALLEGRO_TIMER* timer;
    ALLEGRO_EVENT_QUEUE* queue;
    ALLEGRO_EVENT event;
    ALLEGRO_DISPLAY* display;
    ALLEGRO_FONT* font;
    states active_state;
    bool done;
    bool redraw;
    board* b;
    unsigned char key[ALLEGRO_KEY_MAX]; 
    
} env;

env load_game_env(){
    env e;
    e.active_state = START_SCREEN;
    e.done = false;
    e.redraw = false;
    memset(e.key, 0, sizeof(e.key)); 

    if(!al_init()){
        printf("failed to initialize allegro");
    }

    if(!al_install_keyboard()){
        printf("failed to initialize keyboard");
    }

    if(!al_init_primitives_addon()){
        printf("failed to initialize primatives addon\n");
    }

    //ALLEGRO_TIMER* timer;
    if(!(e.timer=al_create_timer(1.0/FPS))){
        printf("failed to create timer");
    }

    //ALLEGRO_EVENT_QUEUE* queue;
    if(!(e.queue=al_create_event_queue())){
        printf("failed to create event queue");
    }

    //ALLEGRO_DISPLAY* display;
    if(!(e.display=al_create_display(D_WIDHT, D_HEIGHT))){
        printf("failed to create display");
    }

    //ALLEGRO_FONT* font;
    if(!(e.font=al_create_builtin_font())){
        printf("failed to initialize allegro font");
    }

    al_register_event_source(e.queue, al_get_keyboard_event_source());
    al_register_event_source(e.queue, al_get_display_event_source(e.display));
    al_register_event_source(e.queue, al_get_timer_event_source(e.timer));

    return e;
}

void unload_game_env(env* e){
    al_destroy_display(e->display);
    al_destroy_timer(e->timer);
    al_destroy_event_queue(e->queue);
    al_destroy_font(e->font);
}
