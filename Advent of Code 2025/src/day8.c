#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include "day8.h"

double distance(Point* a, Point* b);

int get_answer(const char* filename, long long* answer);

Point* generate_points(const char* filename, int* point_size);