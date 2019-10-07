#include <stdio.h>

#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>

#define D_WIDHT 320
#define D_HEIGHT 400
#define FPS 60

typedef struct {
    ALLEGRO_TIMER* timer;
    ALLEGRO_EVENT_QUEUE* queue;
    ALLEGRO_DISPLAY* display;
    ALLEGRO_FONT* font;
} env;

env load_game_env();
void unload_game_env(env e);
