#include <stdio.h>
#include <allegro5/allegro_primitives.h>

#include "load_game_env.h"
#include "draw_board.h"
#include "board.h"
#include "pieces.h"
#include "play.h"


int main(){

    env _env = load_game_env();
    env* env_ptr = &_env;
    board b = board_initialize();
    env_ptr->b = &b;

    al_start_timer(env_ptr->timer); 

    while(true){
        al_wait_for_event(env_ptr->queue, &(env_ptr->event));
        switch(env_ptr->active_state){
            case PLAY:
                play(env_ptr);
                break;
            case GAMEOVER:
                printf("game over\n");
                break;
            default:
                printf("no state set\n");
                break;
        }

        if(env_ptr->done){
            break;
        }
    }
    
    unload_game_env(env_ptr);
    board_destroy(b);

    return 0;
}
