#include <stdio.h>
#include <stdlib.h>
#include "day9.h"


int getMaxArea(const char* filename, long long* area){
    *area = 0;
    Point points[MAX_POINTS];
    int point_size;
    if (readPointsFromFile(filename, points, &point_size) != 0) {
        return 1;
    }
    BestCorners corners = findBestCorners(points, point_size);
    long long area1 = (long long)(corners.bottom_right.x - corners.top_left.x + 1) * (corners.bottom_right.y - corners.top_left.y + 1);
    long long area2 = (long long)(corners.top_right.x - corners.bottom_left.x+ 1) * (corners.bottom_left.y - corners.top_right.y + 1);
    *area = (area1 > area2) ? area1 : area2;
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
    // first sort by x and y
    qsort(points, point_size, sizeof(Point), compare_point);
    Point best_top_left = points[0];
    Point best_top_right = points[0];
    Point best_bottom_left = points[0];
    Point best_bottom_right = points[0];
    for (int i = 1; i < point_size; i++) {
        if (points[i].x + points[i].y < best_top_left.x + best_top_left.y) {
            best_top_left = points[i];
        }
        if ((-points[i].x) + points[i].y < (-best_top_right.x) + best_top_right.y) {
            best_top_right = points[i];
        }
        if (points[i].x + (-points[i].y) < best_bottom_left.x + (-best_bottom_left.y)) {
            best_bottom_left = points[i];
        }
        if ((-points[i].x) + (-points[i].y) < (-best_bottom_right.x) + (-best_bottom_right.y)) {
            best_bottom_right = points[i];
        }
    }

    BestCorners corners = {best_top_left, best_top_right, best_bottom_left, best_bottom_right};
    return corners;
}


int compare_point(const void* a, const void* b){
    Point* point_a = (Point*)a;
    Point* point_b = (Point*)b;
    if (point_a->y != point_b->y) {
        return point_a->y - point_b->y;
    }
    return point_a->x - point_b->x;
}