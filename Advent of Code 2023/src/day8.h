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

int populate_nodes(FILE* in, Node* nodes, int size, Node* start, Node* goal);

int read_line(const char* line, Node* nodes, int size, Node* start, Node* goal);

Node* find_next(Node* current, const char direction);

#endif // DAY8_H