#include "board.h"
#include "load_game_env.h"
#include <allegro5/allegro_primitives.h>

void draw_board(env* game_env, board* b){
        // draw the board to the screen
        for(int y=PADDING; y<NUM_ROWS-PADDING; y++){ 
            for(int x=PADDING; x<NUM_COLUMNS-PADDING; x++){
                if(b->rows[y]->cells[x]){
                    al_draw_filled_rectangle(
                        10*x,
                        10*y,
                        10*(x+1),
                        10*(y+1),
                        al_map_rgb(255, 0, 0)
                    );
                }
            }
        }

        // draw the piece to the screen
        for(int y=0; y<SIZE; y++){
            for(int x=0; x<SIZE; x++){
                if(b->pieces[b->piece].rotations[b->rotation][y][x]){
                    al_draw_filled_rectangle(
                        10*(x+b->x),
                        10*(y+b->y),
                        10*(x+b->x+1), 
                        10*(y+b->y+1), 
                        al_map_rgb(255, 0, 0)

                    );
                }
            }
        }

        // draw the next piece to the screen
        for(int y=0; y<SIZE; y++){
            for(int x=0; x<SIZE; x++){
                if(b->pieces[b->next_piece].rotations[0][y][x]){
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
        al_draw_textf(game_env->font, al_map_rgb(255, 255, 255), 200, 100, 0, "SCORE: %d", b->score);
        al_draw_textf(game_env->font, al_map_rgb(255, 255, 255), 200, 125, 0, "LEVEL: %d", b->level);
}
