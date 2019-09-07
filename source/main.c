#include <stdio.h>
#include "pieces.h"
#include "board.h"

int main(){

    board b = board_initialize();
    board_print(b);
    printf("\n");
    
    /*
    piece p = piece_factory(I);
    piece_print(p);
    printf("\n");

    p = piece_rotate(p, CLOCK_WISE);
    piece_print(p);
    printf("\n");
    */
    return 0;
}
