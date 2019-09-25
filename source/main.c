#include <stdio.h>

#include "board.h"
#include "pieces.h"

#include <allegro5/allegro5.h>


int main(){
    if(!al_init()){
        printf("failed to initialize allegro");
    }

    return 0;
}
