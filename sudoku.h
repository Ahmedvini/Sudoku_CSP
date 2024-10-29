// sudoku.h
#ifndef SUDOKU_H
#define SUDOKU_H

#define GRID_SIZE 9
#define SUBGRID_SIZE 3

typedef struct {
    int value; // 0 if empty
} Cell;

typedef struct {
    Cell cells[GRID_SIZE][GRID_SIZE];
} Grid;

// Function declarations
void initialize_grid(Grid *grid);
int solve_sudoku(Grid *grid);
int is_safe(Grid *grid, int row, int col, int num);
int find_unassigned_location(Grid *grid, int *row, int *col);

#endif // SUDOKU_H
