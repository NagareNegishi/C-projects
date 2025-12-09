#include <stdio.h>
#include "day9.h"


int getMaxArea(const char* filename, long long* area){
    return 0;
}

int readPointsFromFile(const char* filename, Point* points, int* point_size){
    *point_size = 0;
    FILE* in = fopen(filename, "r");
    if (in == NULL) {
        return 1;
    }
    char buffer[20];
    while (fgets(buffer, sizeof(buffer), in) != NULL) {
        int x, y;
        if (sscanf(buffer, "%d,%d", &x, &y) == 2) {
            points[*point_size].x = x;
            points[*point_size].y = y;
            (*point_size)++;
        } else {
            fclose(in);
            return 1;
        }
    }
    fclose(in);
    return 0;
}

BestCorners findBestCorners(Point* points, int point_size){
    BestCorners corners = {0};
    return corners;
}