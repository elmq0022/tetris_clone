#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "pieces.h"
#define PADDING SIZE // padding for top, bottom, left, and right
#define NUM_COLUMNS 10+PADDING+PADDING
#define NUM_ROWS 20+PADDING+PADDING

#define LEFT -1
#define RIGHT 1
#define DOWN 1

typedef struct {
   int cells[NUM_COLUMNS];
} row;

typedef struct {
    int piece;
    int next_piece;
    int rotation;
    int x;
    int y;
    row* rows[NUM_ROWS];
    int full_rows[NUM_ROWS];
    piece* pieces;
} board;

board board_initialize(){
    board b;

    b.piece = 0;
    b.next_piece = 0;
    b.rotation = 0;
    b.x = (NUM_COLUMNS)/2 - (SIZE)/2;
    b.y = 0;
    b.pieces = p;

    // initialize rand function
    time_t t; 
    srand((unsigned int) time(&t));
    
    for(int i=0; i<NUM_ROWS; i++){
        b.rows[i] = (row*) malloc(sizeof(row));

        for(int j=0; j<NUM_COLUMNS; j++){
            if(i >= NUM_ROWS - PADDING){
                b.rows[i]->cells[j]=2;
            }
            else if(j<PADDING || j >= NUM_COLUMNS - PADDING){
                b.rows[i]->cells[j]=2;
            }
            else {
                b.rows[i]->cells[j] = 0;
            }
        }

        b.full_rows[i] = 0;
    }

    return b;
}

void board_destroy(board b){
    for(int i=0; i<NUM_ROWS; i++){
        free(b.rows[i]);
    }
}

void board_print(board b){
    for(int i=0; i<NUM_ROWS; i++){
        for(int j=0; j<NUM_COLUMNS; j++){
            printf("%d ", b.rows[i]->cells[j]);
        }
        printf("\n");
    }
}

void board_move_row_to_top(board* b, int idx){
    if(idx >= NUM_ROWS){
        printf("not enough rows");
    }
    row* temp = b->rows[idx];
    for(int i=idx; i>0; i--){
        b->rows[i] = b->rows[i-1];
    }
    b->rows[0] = temp;
}

void board_clear_row(board* b, int idx){
    for(int i=0; i<NUM_COLUMNS; i++){
        if(b->rows[idx]->cells[i] != 2){
            b->rows[idx]->cells[i] = 0;
        }
    }
}

int board_is_full_row(board* b, int idx){
    int score = 0;
    for(int i=0; i<NUM_COLUMNS; i++){
        score += b->rows[idx]->cells[i];
    }
    return score == NUM_COLUMNS + PADDING*2;
}

void board_find_full_rows(board* b){
    for(int i=0; i<NUM_ROWS; i++){
        printf("%d %d\n", i, board_is_full_row(b, i));
        b->full_rows[i] = board_is_full_row(b, i);
    }
}

void board_clear_full_rows(board* b){
    for(int i=0; i<NUM_ROWS; i++){
        if(b->full_rows[i]){
            board_clear_row(b, i);
        }
    }
}

void board_move_full_rows(board* b){
    for(int i=0; i<NUM_ROWS; i++){
        if(b->full_rows[i]){
            board_move_row_to_top(b, i);
        }
    }
}

// check the top few rows after a piece is set if the piece was
// set anywhere in the padding area the game is over
int board_is_game_over(board* b){
    for(int i=0; i<PADDING; i++){
        for(int j=PADDING; j< NUM_ROWS-PADDING; j++){
            if(b->rows[i]->cells[j]){
                return 1;
            }
        }
    }
    return 0;
}

int board_is_valid_move(board* b, int x, int y, int rotation){
    // check left and right of board
    if(x < 0 || NUM_COLUMNS-SIZE-1 < x){
        printf("failed for x size \n");
        return 0;
    }

    // check up and down of board
    if(y < 0 || NUM_ROWS-SIZE-1 < y){
        printf("failed for y size \n");
        return 0;
    }

    // check for intersections between board and piece
    for(int i=0; i < SIZE; i++){
        for(int j=0; j < SIZE; j++){
            if(b->rows[i+y]->cells[j+x] && 
               b->pieces[b->piece].rotations[rotation][i][j]
            ){ printf("failed for intersecting with the board \n");
                return 0;
            }
        }
    }

    return 1;
}

int board_rotate_piece(board* b, int direction){
    int new_rotation;
    new_rotation = b->rotation+direction % NUM_ROTATITIONS;
    if(board_is_valid_move(b, b->x, b->y, new_rotation)){
        b->rotation = new_rotation;
        return 1;
    }
    return 0;
}

int board_move_piece(board* b, int x, int y){
    int new_x, new_y;
    new_x = b->x + x;
    new_y = b->y + y;
    if(board_is_valid_move(b, new_x, new_y, b->rotation)){
        b->x = new_x;
        b->y = new_y;
        return 1;
    }
    return 0;
}

int board_set_piece(board* b){
    // copy the pieces to the board
    int x, y, rotation;
    x = b->x;
    y = b->y;
    rotation = b->rotation;

    for(int i=0; i<SIZE; i++){
        for(int j=0; j<SIZE; j++){
            if(
                b->rows[i+y]->cells[j+x] == 1 &&
                b->pieces[b->piece].rotations[rotation][i][j] == 1
            )
            {
                printf("board_set_piece tried to set a location that was already set\n");
                return 0;
            } else if(b->pieces[b->piece].rotations[b->rotation][i][j]){
                b->rows[i+y]->cells[j+x] = 1;
            }
        }
    }
    b->piece = b->next_piece;
    // TODO: Randomly generate next piece
    b->next_piece = rand() % NUM_PIECES;

    b->x = (NUM_COLUMNS)/2 - (SIZE)/2;
    b->y = 0;

    return 1;
}
