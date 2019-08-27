#include <stdio.h>
#include <stdlib.h>
#define NUM_CELLS_IN_ROW 10
#define NUM_ROWS_IN_BOARD 10


typedef struct {
   int cells[NUM_CELLS_IN_ROW];
   int total;
} row;

typedef struct {
    row* rows[NUM_ROWS_IN_BOARD];
} board;

board board_initialize(){
    board b;
    
    for(int i=0; i<NUM_ROWS_IN_BOARD; i++){
        b.rows[i] = (row*) malloc(sizeof(row));
        b.rows[i]->total = i;

        for(int j=0; j<NUM_CELLS_IN_ROW; j++){
            b.rows[i]->cells[j]=i;
        }
    }

    return b;
}

void board_destroy(board b){
    for(int i=0; i<NUM_ROWS_IN_BOARD; i++){
        free(b.rows[i]);
    }
}

void board_print(board b){
    for(int i=0; i<NUM_ROWS_IN_BOARD; i++){
        for(int j=0; j<NUM_CELLS_IN_ROW; j++){
            printf("%d ", b.rows[i]->cells[j]);
        }
        printf(" %d\n", b.rows[i]->total);
    }
}

void board_move_row_to_top(board* b, int idx){
    if(idx >= NUM_ROWS_IN_BOARD){
        printf("not enough rows");
    }
    row* temp = b->rows[idx];
    for(int i=idx; i>0; i--){
        b->rows[i] = b->rows[i-1];
    }
    b->rows[0] = temp;
}

void board_clear_row(board* b, int idx){
    for(int i=0; i<NUM_CELLS_IN_ROW; i++){
        b->rows[idx]->cells[i] = 0;
    }
    b->rows[idx]->total = 0;
}

