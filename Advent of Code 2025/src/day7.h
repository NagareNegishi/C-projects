#ifndef DAY7_H
#define DAY7_H

typedef struct {
    int indexes[150];
    int size;
} Beams;

// Part 1
// we know the case the bean split on the edge of the grid never happens in the input
// and no even number of rows never contains meaningful symbols -> can skip those rows

/**
 * Parse a line of beam input and return the split beams
 */
Beams split_beams(const char* line, Beams* previous_beams, int* total);

int get_total(const char* filename, int* total);
#endif // DAY7_H