#ifndef BOARD_H
#define BOARD_H

#include <stdio.h>
#include <stdlib.h>
#include "pieces.h"
#define PADDING SIZE // padding for top, bottom, left, and right
#define NUM_COLUMNS (10+PADDING+PADDING)
#define NUM_ROWS (20+PADDING+PADDING)

#define LEFT -1
#define RIGHT 1
#define DOWN 1

#define CLOCKWISE 1
#define COUNTER_CLOCK_WISE 3

typedef struct {
   int cells[NUM_COLUMNS];
} row;

typedef struct {
    int piece;
    int next_piece;
    int rotation;
    int x;
    int y;
    row* rows[NUM_ROWS];
    int full_rows[NUM_ROWS];
    piece* pieces;
} board;

board board_initialize();
void board_destroy(board b);
void board_print(board b);
void board_move_row_to_top(board* b, int idx);
void board_clear_row(board* b, int idx);
int board_is_full_row(board* b, int idx);
void board_find_full_rows(board* b);
void board_clear_full_rows(board* b);
void board_move_full_rows(board* b);
int board_is_game_over(board* b);

int board_is_valid_move(board* b, int new_x, int new_y, int rotation);
int board_rotate_piece(board* b, int direction);
int board_move_piece(board* b, int x, int y);
int board_set_piece(board* b);

#endif
