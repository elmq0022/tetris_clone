#define NUM_CELLS_IN_ROW 10
#define NUM_ROWS_IN_BOARD 10

typedef struct {
   int cells[NUM_CELLS_IN_ROW];
   int total;
} row;

typedef struct {
    row* rows[NUM_ROWS_IN_BOARD];
} board;

board board_initialize();

void board_destroy(board b);

void board_print(board b);

void board_move_row_to_top(board* b, int idx);

void board_clear_row(board* b, int idx);
