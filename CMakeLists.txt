# CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(sudoku_csp C)

# Set the C standard to C11
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

# Find PkgConfig
find_package(PkgConfig REQUIRED)

# Find GTK+3 using pkg-config
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

# Add executable
add_executable(sudoku_csp main.c sudoku.c gui.c)

# Include GTK+3 headers
target_include_directories(sudoku_csp PRIVATE ${GTK3_INCLUDE_DIRS})

# Link GTK+3 libraries
target_link_libraries(sudoku_csp PRIVATE ${GTK3_LIBRARIES})

# Add any additional compiler flags
target_compile_options(sudoku_csp PRIVATE ${GTK3_CFLAGS_OTHER})
