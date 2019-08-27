#include <stdio.h>
#include "pieces.h"
#include "board.h"

int main(){
    printf("hello from main");

    board b = board_initialize();
    board_print(b);

    return 0;
}
