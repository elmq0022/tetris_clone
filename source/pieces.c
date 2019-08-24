#include <stdio.h>
#define SIZE 4
#define COUNTER_CLOCK_WISE 1
#define CLOCK_WISE -1


enum colors {RED=1, YELLOW, BLUE, GREEN, ORANGE, PURPLE};

typedef struct{
    int x;
    int y;
} point;


typedef struct{
    enum colors color;
    point points[SIZE];
    point center;
} piece;


void piece_print(piece p){
    for(int i=0; i<SIZE; i++){
        printf("%d, %d\n", p.points[i].x, p.points[i].y);
    }
}


piece piece_rotate(piece p, int direction){
    piece rotated_piece;

    for(int i=0; i<SIZE; i++){
        rotated_piece.points[i].x = -direction*p.points[i].y;
        rotated_piece.points[i].y = direction*p.points[i].x;
    }
    
    return rotated_piece;
}

typedef enum {
    I, J, L, O, S, T, Z
} shape;

piece shape_factory(shape s){
    piece p;
    switch(s){
        
        case I:
            p.points[0].x = 0;
            p.points[1].x = 0;
            p.points[2].x = 0;
            p.points[3].x = 0;

            p.points[0].y = 3;
            p.points[1].y = 1;
            p.points[2].y = -1;
            p.points[3].y = -3;

            p.center.x = 0;
            p.center.y = 1;

            p.color = RED;
            
            break;

        case J:
            p.points[0].x =  0;
            p.points[1].x =  0;
            p.points[2].x =  0;
            p.points[3].x = -2;

            p.points[0].y =  4;
            p.points[1].y =  2;
            p.points[2].y =  0;
            p.points[3].y =  0;

            p.center.x = 0;
            p.center.y = 0;

            p.color = RED;

            break;

            /*
        case L:
            
            p[0].x =  0;
            p[1].x =  0;
            p[2].x =  0;
            p[3].x =  2;

            p[0].y =  4;
            p[1].y =  2;
            p[2].y =  0;
            p[3].y =  0;

            p[0].color = RED;
            p[1].color = RED;
            p[2].color = RED;
            p[3].color = RED;

            break;

        case O:
            
            p[0].x =  1;
            p[1].x =  1;
            p[2].x = -1;
            p[3].x = -1;

            p[0].y =  1;
            p[1].y = -1;
            p[2].y = -1;
            p[3].y =  1;

            p[0].color = RED;
            p[1].color = RED;
            p[2].color = RED;
            p[3].color = RED;
            
            break;

        case S:
            
            p[0].x =  2;
            p[1].x =  0;
            p[2].x =  0;
            p[3].x = -2;

            p[0].y =  1;
            p[1].y =  1;
            p[2].y = -1;
            p[3].y = -1;

            p[0].color = RED; 
            p[1].color = RED;
            p[2].color = RED;
            p[3].color = RED;
            
            break;
            
        case T:
            
            p[0].x = -2;
            p[1].x =  0;
            p[2].x =  2;
            p[3].x =  0;

            p[0].y = 0;
            p[1].y = 0;
            p[2].y = 0;
            p[3].y = 2;

            p[0].color = RED;
            p[1].color = RED;
            p[2].color = RED;
            p[3].color = RED;

            break;

        case Z:
            
            p[0].x = -2;
            p[1].x =  0;
            p[2].x =  0;
            p[3].x =  2;

            p[0].y =   1;
            p[1].y =   1;
            p[2].y =  -1;
            p[3].y =  -1;

            p[0].color = RED;
            p[1].color = RED;
            p[2].color = RED;
            p[3].color = RED;
            
            break;
            */

        default:
            break;
    }
    return p;
}


int main(){

    piece p1; 
    p1 = shape_factory(I);
    piece_print(p1);
    printf("\n");

    p1 = piece_rotate(p1, COUNTER_CLOCK_WISE);
    piece_print(p1);
    printf("\n");

    p1 = shape_factory(J);
    piece_print(p1);
    printf("\n");

    /*
    points_rotate(p1, COUNTER_CLOCK_WISE);
    points_print(p1);
    printf("\n");

    points_rotate(p1, CLOCK_WISE);
    points_print(p1);
    printf("\n");
    */

    return 0;
}
