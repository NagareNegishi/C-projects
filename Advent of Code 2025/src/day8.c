#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include "day8.h"

double distance(Point* a, Point* b){
    int dx = a->x - b->x;
    int dy = a->y - b->y;
    int dz = a->z - b->z;
    return sqrt(dx * dx + dy * dy + dz * dz);
}

int get_answer(const char* filename, long long* answer){
    *answer = 0;
    int point_size = 0;
    Point* points = generate_points(filename, &point_size);
    if(points == NULL){
        return 1;
    }
    return 0;
}

Point* generate_points(const char* filename, int* point_size){
    return NULL;
}