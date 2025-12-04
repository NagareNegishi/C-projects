#ifndef GRID_H
#define GRID_H

typedef struct {
    char** cells;
    int rows;
    int cols;
    int is_valid;
} Grid;

typedef struct {
    int row;
    int col;
    int top;
    int bottom;
    int right;
    int left;
    int is_valid;
} Position;

/**
 * Create a grid from a file.
 */
Grid create_grid(const char* filename);

/**
 * Create a position which represents a cell in the grid,
 * containing its coordinates and boundary information.
 */
Position create_position(int row, int col, Grid* grid);

/**
 * Count the number of occurrences of a target character
 * surrounding a given position in the grid.
 */
int count_target(Grid* grid, Position* pos, char target);


#endif // GRID_H
