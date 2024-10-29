// gui.c
#include "gui.h"
#include <stdlib.h>
#include <string.h>

#define GRID_SIZE 9

// Function prototypes
void update_gui_from_grid(SudokuGUI *gui);
void update_grid_from_gui(SudokuGUI *gui);
void on_solve_button_clicked(GtkButton *button, SudokuGUI *gui);
void on_reset_button_clicked(GtkButton *button, SudokuGUI *gui);

// Initialize the GUI components
void initialize_gui(SudokuGUI *gui, Grid *grid) {
    gui->grid = grid;
    gui->window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(gui->window), "Sudoku Solver");
    gtk_window_set_default_size(GTK_WINDOW(gui->window), 600, 600);
    g_signal_connect(gui->window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(gui->window), vbox);

    GtkWidget *grid_table = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid_table), 5);
    gtk_grid_set_column_spacing(GTK_GRID(grid_table), 5);
    gtk_container_set_border_width(GTK_CONTAINER(grid_table), 10);
    gtk_box_pack_start(GTK_BOX(vbox), grid_table, TRUE, TRUE, 0);

    // Set grid to have homogeneous rows and columns for equal distribution
    gtk_grid_set_column_homogeneous(GTK_GRID(grid_table), TRUE);
    gtk_grid_set_row_homogeneous(GTK_GRID(grid_table), TRUE);

    // Load CSS for styling entries
    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(provider,
        "entry {\n"
        "  border: 1px solid black;\n"
        "  text-align: center;\n" // Center the text
        "  font-size: 18px;\n"    // Increase font size for better visibility
        "}\n",
        -1, NULL);
    GtkStyleContext *context = gtk_widget_get_style_context(gui->window);
    gtk_style_context_add_provider(context,
        GTK_STYLE_PROVIDER(provider),
        GTK_STYLE_PROVIDER_PRIORITY_USER);

    // Create entry widgets for each cell, wrapped in GtkAspectFrame to maintain 1:1 aspect ratio
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            // Create GtkEntry
            GtkWidget *entry = gtk_entry_new();
            gtk_entry_set_max_length(GTK_ENTRY(entry), 1);
            gtk_entry_set_alignment(GTK_ENTRY(entry), 0.5); // Center alignment

            // Create GtkAspectFrame to maintain 1:1 aspect ratio
            GtkWidget *aspect_frame = gtk_aspect_frame_new(NULL, 0.5, 0.5, 1.0, TRUE);
            gtk_container_add(GTK_CONTAINER(aspect_frame), entry);

            // Ensure aspect_frame and entry expand to fill the cell
            gtk_widget_set_hexpand(aspect_frame, TRUE);
            gtk_widget_set_vexpand(aspect_frame, TRUE);
            gtk_widget_set_hexpand(entry, TRUE);
            gtk_widget_set_vexpand(entry, TRUE);

            // Attach the aspect_frame to the grid
            gtk_grid_attach(GTK_GRID(grid_table), aspect_frame, j, i, 1, 1);

            // Store the entry widget in the GUI struct for later access
            gui->cells[i][j] = entry;
        }
    }

    // Create a horizontal box for buttons
    GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

    // Solve button
    GtkWidget *solve_button = gtk_button_new_with_label("Solve");
    g_signal_connect(solve_button, "clicked", G_CALLBACK(on_solve_button_clicked), gui);
    gtk_box_pack_start(GTK_BOX(hbox), solve_button, TRUE, TRUE, 0);

    // Reset button
    GtkWidget *reset_button = gtk_button_new_with_label("Reset");
    g_signal_connect(reset_button, "clicked", G_CALLBACK(on_reset_button_clicked), gui);
    gtk_box_pack_start(GTK_BOX(hbox), reset_button, TRUE, TRUE, 0);

    gtk_widget_show_all(gui->window);
}

// Callback for the Solve button
void on_solve_button_clicked(GtkButton *button, SudokuGUI *gui) {
    update_grid_from_gui(gui);

    if (solve_sudoku(gui->grid)) {
        update_gui_from_grid(gui);
    } else {
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gui->window),
                                                   GTK_DIALOG_DESTROY_WITH_PARENT,
                                                   GTK_MESSAGE_ERROR,
                                                   GTK_BUTTONS_CLOSE,
                                                   "No solution exists for the given Sudoku puzzle.");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    }
}

// Callback for the Reset button
void on_reset_button_clicked(GtkButton *button, SudokuGUI *gui) {
    initialize_grid(gui->grid);  // Assume this function resets the grid in the backend
    update_gui_from_grid(gui);
}

// Update GUI from grid values
void update_gui_from_grid(SudokuGUI *gui) {
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            if (gui->grid->cells[i][j].value != 0) {
                char buffer[2];
                sprintf(buffer, "%d", gui->grid->cells[i][j].value);
                gtk_entry_set_text(GTK_ENTRY(gui->cells[i][j]), buffer);
                gtk_editable_set_editable(GTK_EDITABLE(gui->cells[i][j]), FALSE); // Make cells non-editable after solving
            } else {
                gtk_entry_set_text(GTK_ENTRY(gui->cells[i][j]), "");
                gtk_editable_set_editable(GTK_EDITABLE(gui->cells[i][j]), TRUE); // Allow editing
            }
        }
    }
}

// Update grid from GUI entries
void update_grid_from_gui(SudokuGUI *gui) {
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            const char *text = gtk_entry_get_text(GTK_ENTRY(gui->cells[i][j]));
            if (text[0] >= '1' && text[0] <= '9' && text[1] == '\0') {
                gui->grid->cells[i][j].value = text[0] - '0';
            } else {
                gui->grid->cells[i][j].value = 0;
            }
        }
    }
}
