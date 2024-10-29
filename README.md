# Sudoku Solver with GUI

This project is a Sudoku puzzle solver with a graphical user interface (GUI) built using **C** and **GTK**. It allows users to enter a custom Sudoku puzzle, solve it using a **Constraint Satisfaction Problem (CSP)** approach, and view the solution. The GUI includes a **Solve** button to solve the puzzle and a **Reset** button to clear the grid for a new puzzle input.

## Features

- **Sudoku Puzzle Input**: Users can enter their custom Sudoku puzzle directly into the GUI.
- **Solve Button**: Automatically solves the Sudoku puzzle using the CSP method.
- **Reset Button**: Clears the current puzzle from the grid, allowing for a new puzzle to be entered.
- **1:1 Aspect Ratio**: Ensures each cell in the grid remains square, regardless of window resizing.

## Requirements

- **GTK+3**: This project uses GTK+3 for the graphical interface. Make sure GTK+3 is installed on your system.

### Installing GTK+3 on Ubuntu

To install GTK+3, run:

```bash
sudo apt update
sudo apt install libgtk-3-dev
```
## Compilation and Setup

1.**Clone this repository:**

   ```bash
   git clone https://github.com/Ahmedvini/Sudoku_CSP
   ```
2.**Create a build directory:**

```bash
mkdir build
cd build
```
3.**Run CMake to configure the project:**
```bash
cmake ..
```
4.**Compile the project using make or ninja:**

```bash
make
```
If using Ninja as the generator:

```bash
cmake -G Ninja ..
ninja
```
5.**Run the application:**
```bash
./sudoku_solver
```
## Usage

- **Enter Puzzle**: Type numbers (1-9) into each cell of the grid to set up the Sudoku puzzle.
- **Solve the Puzzle**: Click the **Solve** button to automatically solve the puzzle. The solution will be displayed in the grid.
- **Reset the Puzzle**: Click the **Reset** button to clear the grid and input a new puzzle.
## Project Structure

```plaintext
sudoku_solver/
├── gui.c                 # GUI implementation with GTK+3
├── gui.h                 # Header file for GUI functions
├── main.c                # Main program entry point
├── sudoku.c              # Sudoku solving logic using CSP
├── sudoku.h              # Header file for Sudoku solving functions
└── README.md             # Project documentation
```
## Key Files

- **`gui.c`**: Contains the GUI logic, setting up the window, handling user input, and creating buttons.
- **`sudoku.c`**: Implements the CSP method for solving the Sudoku puzzle.
- **`main.c`**: Entry point for the application, initializing the GUI and starting the GTK main loop.

## Dependencies

- **GTK+3**: Required for the graphical interface.
- **CMake**: Used for configuring and building the project.
- **C Compiler**: Tested with GCC.
  
## Troubleshooting

- **GTK+3 Not Found**: Ensure GTK+3 is installed and accessible. Use `pkg-config` to check:

  ```bash
  pkg-config --cflags --libs gtk+-3.0
  ```

- **Compilation Issues**: If you encounter errors, ensure that all dependencies are correctly installed and try cleaning the build directory:

  ```bash
  rm -rf build
  mkdir build
  cd build
  cmake ..
  make
  ```
## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments

This project was developed as a learning exercise in C programming, GUI design with GTK, and applying CSP methods to solve constraint-based problems like Sudoku.


   

