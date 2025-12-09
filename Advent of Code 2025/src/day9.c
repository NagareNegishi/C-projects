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
    printf("Sorted points:\n");
    for (int i = 0; i < point_size; i++) {
        printf("(%d, %d)\n", points[i].x, points[i].y);
    }
    Point best_top_left = points[0];
    Point best_top_right = points[0];
    Point best_bottom_left = points[0];
    Point best_bottom_right = points[0];
    // then find best corners
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



// part2 raycasting
int getMaxArea_v2(const char* filename, long long* area){
    *area = 0;
    Point points[MAX_POINTS];
    int point_size;
    if (readPointsFromFile(filename, points, &point_size) != 0) {
        return 1;
    }

    // For each pair of red tiles
    for (int i = 0; i < point_size; i++) {
        for (int j = i + 1; j < point_size; j++) {
            // Get rectangle bounds
            int x1 = (points[i].x < points[j].x) ? points[i].x : points[j].x;
            int x2 = (points[i].x > points[j].x) ? points[i].x : points[j].x;
            int y1 = (points[i].y < points[j].y) ? points[i].y : points[j].y;
            int y2 = (points[i].y > points[j].y) ? points[i].y : points[j].y;
            
            // Check if ALL tiles in rectangle are red or green
            int valid = 1;
            for (int y = y1; y <= y2 && valid; y++) {
                for (int x = x1; x <= x2 && valid; x++) {
                    Point p = {x, y};
                    if (!isRedOrGreen(p, points, point_size)) {
                        valid = 0;
                    }
                }
            }
            
            if (valid) {
                long long candidate = (long long)(x2 - x1 + 1) * (y2 - y1 + 1);
                // Update max area if larger
                if (candidate > *area) {
                    *area = candidate;
                }
            }
        }
    }
    return 0;
}


// Check if a point is inside a polygon using ray casting
int isPointInPolygon(Point point, Point* polygon, int n) {
    int inside = 0;
    
    for (int i = 0, j = n - 1; i < n; j = i++) {
        int xi = polygon[i].x, yi = polygon[i].y;
        int xj = polygon[j].x, yj = polygon[j].y;
        
        // Check if horizontal ray from point crosses edge (j -> i)
        int intersect = ((yi > point.y) != (yj > point.y)) &&
                       (point.x < (xj - xi) * (point.y - yi) / (yj - yi) + xi);
        
        if (intersect) {
            inside = !inside;
        }
    }
    
    return inside;
}

// Check if a point is on the polygon boundary
int isPointOnBoundary(Point point, Point* polygon, int n) {
    for (int i = 0, j = n - 1; i < n; j = i++) {
        Point p1 = polygon[j];
        Point p2 = polygon[i];
        
        // Check if point is on line segment between p1 and p2
        if (p1.x == p2.x) {  // Vertical line
            if (point.x == p1.x &&
                point.y >= (p1.y < p2.y ? p1.y : p2.y) &&
                point.y <= (p1.y > p2.y ? p1.y : p2.y)) {
                return 1;
            }
        } else if (p1.y == p2.y) {  // Horizontal line
            if (point.y == p1.y &&
                point.x >= (p1.x < p2.x ? p1.x : p2.x) &&
                point.x <= (p1.x > p2.x ? p1.x : p2.x)) {
                return 1;
            }
        }
    }
    return 0;
}

// Check if point is red or green (on/inside polygon)
int isRedOrGreen(Point point, Point* redTiles, int n) {
    return isPointOnBoundary(point, redTiles, n) || isPointInPolygon(point, redTiles, n);
}