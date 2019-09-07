#include <stdio.h>
#include <stdlib.h>
#include "pieces.h"
#define PADDING SIZE // padding for top, bottom, left, and right
#define NUM_COLUMNS 10+PADDING+PADDING
#define NUM_ROWS 20+PADDING+PADDING

#define LEFT -1
#define RIGHT 1
#define DOWN 1

typedef struct {
   int cells[NUM_COLUMNS];
   int total;
} row;

typedef struct {
    int piece;
    int next_piece;
    int rotation;
    int x;
    int y;
    row* rows[NUM_ROWS];
    piece* pieces;
} board;

board board_initialize(){
    board b;

    b.piece = 0;
    b.next_piece = 0;
    b.rotation = 0;
    b.x = NUM_COLUMNS/2 - SIZE/2;
    b.y = 0;
    b.pieces = p;
    
    for(int i=0; i<NUM_ROWS; i++){
        b.rows[i] = (row*) malloc(sizeof(row));
        b.rows[i]->total = i;

        for(int j=0; j<NUM_COLUMNS; j++){
            if(i >= NUM_ROWS - PADDING){
                b.rows[i]->cells[j]=1;
            }
            else if(j<PADDING || j >= NUM_COLUMNS - PADDING){
                b.rows[i]->cells[j]=1;
            }
            else {
                b.rows[i]->cells[j] = 0;
            }
        }
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
        printf(" %d\n", b.rows[i]->total);
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
    for(int i=PADDING; i<NUM_COLUMNS-PADDING; i++){
        b->rows[idx]->cells[i] = 0;
    }
    b->rows[idx]->total = 0;
}

int board_is_valid_move(board* b, int x, int y, int rotation){
    // check left and right of board
    if(x < 0 || NUM_COLUMNS-SIZE-1 < x){
        return 0;
    }

    // check up and down of board
    if(y < 0 || NUM_COLUMNS-SIZE-1 < y){
        return 0;
    }

    // check for intersections between board and piece
    for(int i=0; i < SIZE; i++){
        for(int j=0; j < SIZE; j++){
            if(b->rows[i+y]->cells[j+x] == 1 && 
               b->pieces[b->piece].rotations[rotation][i][j] == 1
            ){
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
