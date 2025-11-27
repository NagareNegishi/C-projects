#include <stdio.h>
#include "day8.h"

/**
 * Counts the number of steps required to complete the task defined in the input file.
 * @param filename The path to the input file.
 * @param steps Pointer to an integer where the result will be stored.
 */
int count_steps(const char* filename, int* steps){
    FILE* in = fopen(filename, "r");
    if (in == NULL){
        return 1;
    }
    char directions[1000];
    if (fgets(directions, sizeof(directions), in) == NULL) {
        fclose(in);
        return 1;
    }
    fgets(directions, sizeof(directions), in); // skip line

    Node nodes[17576];
    Node start = {0};
    Node goal = {0};
    if (populate_nodes(in, nodes, 17576, &start, &goal) == 0) {
        fclose(in);
        return 1;
    }
    return 0;
}

int populate_nodes(FILE* in, Node* nodes, int size, Node* start, Node* goal)
{
    char buffer[20];
    while (fgets(buffer, sizeof(buffer), in) != NULL) {
        if (read_line(buffer, nodes, size, start, goal) == 1) {
            return 1;
        }

    }
    fclose(in);
    return 0;
}

int read_line(const char* line, Node* nodes, int size, Node* start, Node* goal)
{
    char names[3][4]; // this, left, right
    if (sscanf(line, "%s = (%s %s)", names[0], names[1], names[2]) != 3) {
        return 1;
    }
    Node temp[3] = {0};
    for (int i = 0; i < 3; i++) {
        names[i][3] = '\0'; // ensure null-termination
        temp[i] = create_node(names[i]);
        if (temp[i].is_valid == false) {
            return 1;
        }
        if (nodes[temp[i].code].is_valid == false) {
            nodes[temp[i].code] = temp[i];
        }
    }
    if (start->is_valid == false) {
        *start = temp[0];
    }
    *goal = temp[0];
    nodes[temp[0].code].left = &nodes[temp[1].code];
    nodes[temp[0].code].right = &nodes[temp[2].code];
    return 0;
}

Node* find_next(Node* current, const char direction){
    return NULL;
}