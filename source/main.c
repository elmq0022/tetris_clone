#include <stdio.h>
#include <allegro5/allegro_primitives.h>

#include "load_game_env.h"
#include "draw_board.h"
#include "board.h"
#include "pieces.h"
#include "play.h"
#include "gameover.h"


int main(){

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
            case PLAY:
                update = (&play_update);
                draw = (&play_draw);
                break;
            case GAMEOVER:
                update = (&update_gameover);
                draw = (&draw_gameover);
                break;
            default:
                printf("no state set\n");
                break;
        }
        //update game logic
        update(env_ptr);
        
        //draw to the screen
        if(env_ptr->redraw && al_event_queue_is_empty(env_ptr->queue)){
            al_clear_to_color(al_map_rgb(0, 0, 0));
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
