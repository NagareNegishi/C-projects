#ifndef DAY10_H
#define DAY10_H
#include "point.h"
#include <stdio.h>

int get_steps(const char* filename, long *steps);

char* read_map(FILE* in, int* rows, int* cols, Point* start);

int trace_path(const char* map, const int rows, const int cols, Point* start, long *steps);


#endif // DAY10_H