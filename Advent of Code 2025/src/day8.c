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
    Point points[MAX_N] = {0};
    if (generate_points(filename, points, &point_size) != 0) {
        return 1;
    }

    return 0;
}

int generate_points(const char* filename, Point* points, int* point_size){
    FILE* in = fopen(filename, "r");
    if(in == NULL){
        return 1;
    }
    *point_size = 0;
    char buffer[256];
    
    while (fgets(buffer, sizeof(buffer), in) != NULL) {
        if(*point_size >= MAX_N){
            perror("Exceeded maximum number of points");
            break;
        }
        if (sscanf(buffer, "%d,%d,%d", &points[*point_size].x, &points[*point_size].y, &points[*point_size].z) != 3) {
            perror("Invalid point format");
            fclose(in);
            return 1;
        }
        (*point_size)++;
    }
    fclose(in);
    return 0;
}