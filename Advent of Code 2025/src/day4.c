#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "day4.h"
#include "grid.h"

int count_total(const char* filename, int* total){
    *total = 0;
    Grid grid = create_grid(filename);
    if (!grid.is_valid) {
        cleanUp(&grid);
        return 1;
    }
    char** lines = grid.cells;
    for (int r = 0; r < grid.rows; r++) {
        char *line = lines[r];
        for (int c = 0; c < grid.cols; c++) {
            char ch = line[c];
            if (ch == '@') {
                Position pos = create_position(r, c, &grid);
                if (!pos.is_valid) {
                    cleanUp(&grid);
                    return 1;
                }
                int count = count_target(&grid, &pos, '@');
                if (count < 4) {
                    (*total)++;
                }
            }
        }
    }
    return 0;
}

void cleanUp(Grid* grid) {
    for (int r = 0; r < grid->rows; r++) {
        free(grid->cells[r]);
    }
    free(grid->cells);
}


// part 2
int count_total_v2(const char* filename, int* total){
    *total = 0;
    Grid grid = create_grid(filename);
    if (!grid.is_valid) {
        cleanUp(&grid);
        return 1;
    }
    char** lines = grid.cells;
    for (int r = 0; r < grid.rows; r++) {
        char *line = lines[r];
        for (int c = 0; c < grid.cols; c++) {
            char ch = line[c];
            if (ch == '@') {
                Position pos = create_position(r, c, &grid);
                if (!pos.is_valid) {
                    cleanUp(&grid);
                    return 1;
                }
                int count = count_target(&grid, &pos, '@');
                if (count < 4) {
                    (*total)++;
                }
            }
        }
    }
    return 0;
}