#ifndef DAY9_H
#define DAY9_H

/**
 * largest area can be made from:
 * - best top left corner and bottom right corner
 * - or best top right corner and bottom left corner
 *
 * File input is random, so first I need to read all point and sort them by x and y
 */

#define MAX_POINTS 500

typedef struct {
    int x;
    int y;
} Point;


typedef struct {
    Point top_left;
    Point top_right;
    Point bottom_left;
    Point bottom_right;
} BestCorners;

int getMaxArea(const char* filename, long long* area);

int readPointsFromFile(const char* filename, Point* points, int* point_size);

BestCorners findBestCorners(Point* points, int point_size);

int compare_point(const void* a, const void* b);


#endif // DAY9_H