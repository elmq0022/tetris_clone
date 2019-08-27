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


void piece_print(piece p);

piece piece_rotate(piece p, int direction);

typedef enum {
    I, J, L, O, S, T, Z
} shape;

piece shape_factory(shape s);
