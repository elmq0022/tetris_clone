#include <stdio.h>
#include <allegro5/allegro_primitives.h>

#include "board.h"
#include "draw_board.h"
#include "gameover.h"
#include "load_game_env.h"
#include "play.h"
#include "start_screen.h"

#include "high_score.h"
#include "high_score_scene.h"

int main(){
    // TODO: move this somwhere else:W
    int arr[10];
    high_score_load(arr, 10);
    for(int i=0; i<10; i++){
        printf("%d\n", arr[i]);
    }

    high_score_add_score(arr, 10, 20); 
    for(int i=0; i<10; i++){
        printf("%d\n", arr[i]);
    }

    high_score_write(arr, 10);
    high_score_load(arr, 10);
    for(int i=0; i<10; i++){
        printf("%d\n", arr[i]);
    }
    // end TODO

    env _env = load_game_env();
    env* env_ptr = &_env;
    board b = board_initialize();
    env_ptr->b = &b;

    void (*update)(env*);
    void (*draw)(env*);

    al_start_timer(env_ptr->timer); 

    while(true){
        al_wait_for_event(env_ptr->queue, &(env_ptr->event));

        switch(env_ptr->active_state){
            case START_SCREEN:
                update = (&update_start_screen);
                draw = (&draw_start_screen);
                break;
            case PLAY:
                update = (&play_update);
                draw = (&play_draw);
                break;
            case GAMEOVER:
                update = (&update_gameover);
                draw = (&draw_gameover);
                break;
            case HIGH_SCORE:
                update = (&update_high_score);
                draw = (&draw_high_score);
                break;
            default:
                printf("no state set\n");
                break;
        }

        switch(env_ptr->event.type){
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                env_ptr->done = true;
                break;

            // store key events in an unsigned char array
            case ALLEGRO_EVENT_KEY_DOWN:
                env_ptr->key[env_ptr->event.keyboard.keycode] = KEY_SEEN | KEY_RELEASED;
                break;

            case ALLEGRO_EVENT_KEY_UP:
                env_ptr->key[env_ptr->event.keyboard.keycode] &= KEY_RELEASED;
                break;

            // process logic for state update
            case ALLEGRO_EVENT_TIMER:
                update(env_ptr);

                for(int i=0; i<ALLEGRO_KEY_MAX; i++){
                    env_ptr->key[i] &= KEY_SEEN;
                }
                
                env_ptr->redraw = true;
                break;

            default:
                break;
        } 

        
        //draw to the screen
        if(env_ptr->redraw && al_event_queue_is_empty(env_ptr->queue)){
            al_clear_to_color(al_map_rgb(0, 0, 0));

            // draw as dictated by game state
            draw(env_ptr);

            al_flip_display();
            env_ptr->redraw = false;
        }

        if(env_ptr->done){
            break;
        }
    }
    
    unload_game_env(env_ptr);
    board_destroy(b);

    return 0;
}
