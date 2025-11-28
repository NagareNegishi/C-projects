#ifndef DAY8_H
#define DAY8_H
#include <stdio.h>
#include "node.h"

/**
 * Counts the number of steps required to complete the task defined in the input file.
 * @param filename The path to the input file.
 * @param steps Pointer to an integer where the result will be stored.
 */
int count_steps(const char* filename, int* steps);

/**
 * Populates the nodes array from the input file.
 */
int populate_nodes(FILE* in, Node* nodes, int* start, int* goal);

/**
 * Reads a line from the input file and populates the nodes array.
 */
int read_line(const char* line, Node* nodes, int* start, int* goal);



// part 2
// need to detect cycle

typedef struct {
    int dir_pos;
    int step;
} Record;

int find_cycle(Node* nodes, const int start, const char* directions, const int len, int* cycle_from, int* cycle_len);
int count_steps_v2(const char* filename, long long* steps);
int populate_nodes_v2(FILE* in, Node* nodes, int** start, int* size);
int read_line_v2(const char* line, Node* nodes, int** start, int* size);

#endif // DAY8_H