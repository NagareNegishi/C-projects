#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "helper/helper.h"
#include "galaxy.h"
#include "day11.h"

int get_sum(const char* filename, long long* sum){
    *sum = 0;
    FILE* in = fopen(filename, "r");
    if (in == NULL) {
        perror("Failed to open file");
        return -1;
    }
    int galaxy_rows[200] = {-1};
    int galaxy_cols [200] = {-1};
    int list_size;
    int col_size = 200;
    int row_size = 200;
    Galaxy *list = process_data(in, &list_size, galaxy_rows, galaxy_cols, &col_size, &row_size);
    fclose(in);
    if (list == NULL) {
        perror("Failed to process data");
        return -1;
    }

    for (int i = 0; i < list_size; i++) {
        for (int j = i + 1; j < list_size; j++) {
            int distance = get_distance(&list[i], &list[j], galaxy_cols, galaxy_rows, col_size, row_size);
            *sum += distance;
        }
    }
    free(list);
    return 0;
}

Galaxy* process_data(FILE* in, int* galaxy_size, int* galaxy_rows, int* galaxy_cols,
    int* col_size, int* row_size){
    char buffer[2000];
    int galaxy_count = 0;
    int galaxy_row_count = 0;
    int galaxy_col_count = 0;
    int row = 0;
    Galaxy *list = NULL;
    while (fgets(buffer, sizeof(buffer), in) != NULL) {
        char *current = buffer;
        int find = 0;
        while ((current = strchr(current, '#')) != NULL) {
            // add Galaxy
            Galaxy *temp = realloc(list, sizeof(Galaxy) * (galaxy_count + 1));
            if (temp == NULL) {
                free(list);
                return NULL;
            }
            list = temp;
            int col = current - buffer;
            Galaxy g = {
                .id = galaxy_count,
                .row = row,
                .col = col
            };
            list[galaxy_count] = g;
            galaxy_count++;
            find++;

            // update col list
            if (!contains(galaxy_cols, galaxy_col_count, col)) {
                galaxy_cols[galaxy_col_count] = col;
                galaxy_col_count++;
            }
            current++;
        }
        // update row list
        if (find) {
            if (!contains(galaxy_rows, galaxy_row_count, row)) {
                galaxy_rows[galaxy_row_count] = row;
                galaxy_row_count++;
            }
        }
        row++;
    }
    *galaxy_size = galaxy_count;
    *col_size = galaxy_col_count;
    *row_size = galaxy_row_count;
    return list;
}