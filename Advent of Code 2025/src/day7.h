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


//part 2
// I need to make tree structure to represent the beam splits
// and make recursive function to traverse the tree and count the possible paths

typedef struct BeamNode {
    struct BeamNode* left;
    struct BeamNode* right;
    int left_index;
    int right_index;
} BeamNode;



int get_total_v2(const char* filename, long long* total);
#endif // DAY7_H