// main.c
#include "sudoku.h"
#include "gui.h"

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    Grid grid;
    initialize_grid(&grid);

    SudokuGUI gui;
    initialize_gui(&gui, &grid);

    gtk_main();
    return 0;
}
