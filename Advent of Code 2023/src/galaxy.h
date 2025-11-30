#ifndef GALAXY_H
#define GALAXY_H

typedef struct {
    int id;
    int row;
    int col;
} Galaxy;


int get_distance(Galaxy *a, Galaxy *b, const int* cols, const int* rows,
    const int col_size, const int row_size);

#endif