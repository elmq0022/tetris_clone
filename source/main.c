#include <stdio.h>
#include "pieces.h"
#include "board.h"

int main(){

    board b = board_initialize();
    board_print(b);
    printf("\n");

    piece_print(b.pieces[b.piece], b.rotation);
    printf("\n");

    int x, y;
    x = y = 0;

    printf("x: %d y: %d valid: %d \n", x, y, board_is_valid_move(&b, x, y, 0));
    
    return 0;
}
