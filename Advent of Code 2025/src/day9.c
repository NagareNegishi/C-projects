#include <stdio.h>
#include "day9.h"


int getMaxArea(const char* filename, long long* area);

int readPointsFromFile(const char* filename, Point* points, int* point_size);

BestCorners findBestCorners(Point* points, int point_size);