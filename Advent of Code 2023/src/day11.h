#ifndef DAY11_H
#define DAY11_H
#include "galaxy.h"
#include <stdio.h>

int get_sum(const char* filename, long long* sum);

Galaxy* process_data(FILE* in, int* galaxy_size, int* galaxy_rows, int* galaxy_cols,
    int* col_size, int* row_size);


#endif // DAY11_H