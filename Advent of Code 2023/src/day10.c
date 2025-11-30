#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "point.h"
#include "day10.h"

int get_steps(const char* filename, long *steps){
    FILE* in = fopen(filename, "r");
    if (in == NULL) {
        return 0; // file not found
    }

    
    int rows;
    int cols;
    Point start = {0};
    char *map = read_map(in, &rows, &cols, &start);
    fclose(in);
    if (map == NULL) {
        return 0;
    }

    int trace_result = trace_path(map, rows, cols, &start, steps);
    free(map);
    if (trace_result == 0) {
        return 0;
    }
    *(steps) = *(steps)/2;
    return 1; // success
}

char* read_map(FILE* in, int* rows, int* cols, Point* start){
    *rows = 0;
    *cols = 0;
    int col_len = 0;
    int current_row = 0;
    char buffer[1000];
    char *map = NULL;
    while (fgets(buffer, sizeof(buffer), in) != NULL) {
        // check start
        char *s = strchr(buffer, 'S');
        if (s != NULL) {
            int start_col = s - buffer;
            start->col = start_col;
            start->row = current_row;
        }

        // copy lines
        if (col_len == 0) {
            col_len = strlen(buffer) - 1; // remove \n
        }
        buffer[col_len] = '\0'; // remove \n
        char *temp = realloc(map, col_len * (current_row + 1));
        if (temp == NULL) {
            free(map);
            return NULL;
        }
        map = temp;
        memcpy(&map[(current_row * col_len)], buffer, col_len);
        current_row++;
        
    }
    *rows = current_row;
    *cols = col_len;
    return map;
}

int trace_path(const char* map, const int rows, const int cols, Point* start, long *steps){
    *steps = 0;
    *start = search_option(NONE, map, start->row, start->col, rows, cols);
    Point current = *start;
    int next_row;
    int next_col;
    int max_steps = rows * cols; // prevent infinite loop
    while (*steps < max_steps) {
        // find next position
        switch (current.out)
        {
        case UP:
            next_row = current.row - 1;
            next_col = current.col;
            break;
        case RIGHT:
            next_row = current.row;
            next_col = current.col + 1;
            break;
        case DOWN:
            next_row = current.row + 1;
            next_col = current.col;
            break;
        case LEFT:
            next_row = current.row;
            next_col = current.col - 1;
            break;
        default:
            return 0; // invalid direction
        }
        current = search_option(current.out, map, next_row, next_col, rows, cols);
        (*steps)++;
        if (current.tile == START) {
            break;
        }
        if (!current.is_vaild) {
            return 0; // invalid path
        }
    }
    return 1;
}

