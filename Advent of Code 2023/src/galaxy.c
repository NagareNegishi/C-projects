#include <stdio.h>
#include "galaxy.h"
#include "helper.h"

int get_distance(Galaxy *a, Galaxy *b, const int* cols, const int* rows,
    const int col_size, const int row_size){
        if (a == NULL || b == NULL || cols == NULL || rows == NULL || col_size <= 0 || row_size <= 0) {
            perror("Invalid input to get_distance");
            return 0;
        }
        // determine both endpoints
        int start_col;
        int start_row;
        int end_col;
        int end_row;
        if (a->col <= b->col) {
            start_col = a->col;
            end_col = b->col;
        } else {
            start_col = b->col;
            end_col = a->col;
        }
        if (a->row <= b->row) {
            start_row = a->row;
            end_row = b->row;
        } else {
            start_row = b->row;
            end_row = a->row;
        }
        // calculate distance
        int distance = (end_row - start_row) + (end_col - start_col);
        for (int c = start_col + 1; c < end_col; c++) {
            if (!contains(cols, col_size, c)) {
                distance++;
            }
        }
        for (int r = start_row + 1; r < end_row; r++) {
            if (!contains(rows, row_size, r)) {
                distance++;
            }
        }
        return distance;
    }