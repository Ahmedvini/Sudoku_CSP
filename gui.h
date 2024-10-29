// gui.h
#ifndef GUI_H
#define GUI_H

#include <gtk/gtk.h>
#include "sudoku.h"

typedef struct {
    GtkWidget *window;
    GtkWidget *cells[GRID_SIZE][GRID_SIZE];
    Grid *grid;
} SudokuGUI;

// Function declarations
void initialize_gui(SudokuGUI *gui, Grid *grid);
void on_solve_button_clicked(GtkButton *button, SudokuGUI *gui);
void on_reset_button_clicked(GtkButton *button, SudokuGUI *gui);
void update_gui_from_grid(SudokuGUI *gui);

#endif // GUI_H
