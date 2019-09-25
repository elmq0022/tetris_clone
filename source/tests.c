#include <stdio.h>

#include "board.h"
#include "pieces.h"

int tests(){

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

    
    while(board_move_piece(&b, LEFT, 0)){
        printf("moving left\n");
    }

    while(board_move_piece(&b, 0, DOWN)){
        printf("droping\n");
    }

    board_set_piece(&b);
    board_print(b);
    b.piece = 0;
    

    while(board_move_piece(&b, RIGHT, 0)){
        printf("moving left\n");
    }

    while(board_move_piece(&b, 0, DOWN)){
        printf("droping\n");
    }

    board_set_piece(&b);
    board_print(b);
    b.piece = 0;


    board_rotate_piece(&b, CLOCK_WISE);
    while(board_move_piece(&b, 0, DOWN)){
        printf("droping\n");
    }

    board_set_piece(&b);
    board_print(b);
    b.piece = 0;
    
    board_move_piece(&b, LEFT, 0);
    while(board_move_piece(&b, 0, DOWN)){
        printf("droping\n");
    }

    board_set_piece(&b);
    board_print(b);
    printf("\n");
    b.piece = 0;
    
    // clean up after piece is dropped
    board_find_full_rows(&b);
    board_print(b);
    printf("\n");

    board_clear_full_rows(&b);
    board_print(b);
    printf("\n");

    board_move_full_rows(&b);
    board_print(b);
    printf("\n");

    return 0;
}
