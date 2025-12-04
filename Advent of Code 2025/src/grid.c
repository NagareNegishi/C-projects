#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grid.h"


/**
 * Create a grid from a file.
 */
Grid create_grid(const char* filename){
    FILE* in = fopen(filename, "r");
    Grid grid = {0};
    if (!in) { return grid;}

    int rows = 0;
    int cols = -1;
    char** cells = NULL;
    char buffer[1024];

    while (fgets(buffer, sizeof(buffer), in) != NULL) {
        if (buffer[0] == '\n') { // empty line indicates end of grid
            break;
        }
        // expecting uniform row lengths
        if (cols == -1) {
            int len = strlen(buffer);
            if (buffer[len - 1] == '\n') {
                buffer[len - 1] = '\0';
                len--;
            }
            cols = len;
        }
        char* row = (char*)calloc(cols + 1, sizeof(char));
        if (row == NULL) {
            goto cleanup;
        }
        strncpy(row, buffer, cols);
        char** temp = (char**)realloc(cells, (rows + 1) * sizeof(char*));
        if (temp == NULL) {
            free(row);
            goto cleanup;
        }
        cells = temp;
        cells[rows] = row;
        rows++;
    }

    fclose(in);
    grid.cells = cells;
    grid.rows = rows;
    grid.cols = cols;
    grid.is_valid = 1;
    return grid;

cleanup:
    for (int r = 0; r < rows; r++) {
        free(cells[r]);
    }
    free(cells);
    fclose(in);
    return grid;
}

/**
 * Create a position which represents a cell in the grid,
 * containing its coordinates and boundary information.
 */
Position create_position(int row, int col, Grid* grid){
    Position pos = {0};
    pos.row = row;
    pos.col = col;
    if (grid == NULL || !grid->is_valid || row < 0 || col < 0 ||
        row >= grid->rows || col >= grid->cols) {
        return pos; // invalid position
    }
    pos.top = (row > 0) ? row - 1 : row;
    pos.bottom = (row < grid->rows - 1) ? row + 1 : row;
    pos.left = (col > 0) ? col - 1 : col;
    pos.right = (col < grid->cols - 1) ? col + 1 : col;
    pos.is_valid = 1;
    return pos;
}

/**
 * Count the number of occurrences of a target character
 * surrounding a given position in the grid.
 */
int count_target(Grid* grid, Position* pos, char target){
    if (grid == NULL || !grid->is_valid || pos == NULL || !pos->is_valid) {
        return 0;
    }
    int count = 0;
    for (int r = pos->top; r <= pos->bottom; r++) {
        for (int c = pos->left; c <= pos->right; c++) {
            if (r == pos->row && c == pos->col) {
                continue; // skip the position itself
            }
            if (grid->cells[r][c] == target) {
                count++;
            }
        }
    }
    return count;
}