#include <stdio.h>

#include "board.h"
#include "pieces.h"

int main(){

    board b = board_initialize();
    board_print(b);
    printf("\n");

    piece_print(b.pieces[b.piece], b.rotation);
    printf("\n");

    int x, y;

    x = y = 0;
    printf("x: %d y: %d valid: %d \n", x, y, board_is_valid_move(&b, x, y, 0));

    x = 4;
    printf("x: %d y: %d valid: %d \n", x, y, board_is_valid_move(&b, x, y, 0));

    x = 10;
    printf("x: %d y: %d valid: %d \n", x, y, board_is_valid_move(&b, x, y, 0));
    
    x = 4; y = 22;
    printf("x: %d y: %d valid: %d \n", x, y, board_is_valid_move(&b, x, y, 0));

    x = 4; y = 23;
    printf("x: %d y: %d valid: %d \n", x, y, board_is_valid_move(&b, x, y, 0));

    
    board_rotate_piece(&b, CLOCK_WISE);
    while(board_move_piece(&b, 0, DOWN)){
        printf("droping\n");
    }

    board_set_piece(&b);
    board_print(b);

    board_rotate_piece(&b, CLOCK_WISE);
    while(board_move_piece(&b, 0, DOWN)){
        printf("droping\n");
    }

    board_set_piece(&b);
    board_print(b);

    return 0;
}
