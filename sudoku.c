// sudoku.c
#include <stdio.h>
#include "sudoku.h"

// Initialize the grid with zeros
void initialize_grid(Grid *grid) {
    for(int i = 0; i < GRID_SIZE; i++) {
        for(int j = 0; j < GRID_SIZE; j++) {
            grid->cells[i][j].value = 0;
        }
    }
}

// Check if a number is safe to place
int is_safe(Grid *grid, int row, int col, int num) {
    for (int x = 0; x < GRID_SIZE; x++) {
        if (grid->cells[row][x].value == num || grid->cells[x][col].value == num) {
            return 0;
        }
    }
    
    int startRow = row - row % SUBGRID_SIZE;
    int startCol = col - col % SUBGRID_SIZE;
    for (int i = 0; i < SUBGRID_SIZE; i++) {
        for (int j = 0; j < SUBGRID_SIZE; j++) {
            if (grid->cells[i + startRow][j + startCol].value == num) {
                return 0;
            }
        }
    }
    return 1;
}

// Find unassigned cell location
int find_unassigned_location(Grid *grid, int *row, int *col) {
    for (*row = 0; *row < GRID_SIZE; (*row)++) {
        for (*col = 0; *col < GRID_SIZE; (*col)++) {
            if (grid->cells[*row][*col].value == 0) {
                return 1;
            }
        }
    }
    return 0;
}

// Solve Sudoku using backtracking
int solve_sudoku(Grid *grid) {
    int row, col;
    if (!find_unassigned_location(grid, &row, &col)) {
        return 1; // Puzzle solved
    }

    for (int num = 1; num <= GRID_SIZE; num++) {
        if (is_safe(grid, row, col, num)) {
            grid->cells[row][col].value = num;
            if (solve_sudoku(grid)) {
                return 1;
            }
            grid->cells[row][col].value = 0; // Backtrack
        }
    }
    return 0;
}
