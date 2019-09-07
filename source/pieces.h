#ifndef PIECIES_H
#define PIECIES_H
#define SIZE 5
#define NUM_PIECES 7
#define NUM_ROTATITIONS 4
#define COUNTER_CLOCK_WISE 3
#define CLOCK_WISE 1 

enum colors {RED=1, YELLOW, BLUE, GREEN, ORANGE, PURPLE};

typedef struct{
    enum colors color;
    int rotations[NUM_ROTATITIONS][SIZE][SIZE];
} piece;

typedef enum {
    I=0, J, L, O, S, T, Z
} shape;

void piece_print(piece p, int r);

piece p[NUM_PIECES];
#endif
