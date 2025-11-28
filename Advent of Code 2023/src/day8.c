#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "day8.h"
#include "my_math.h"
#include <stdbool.h>

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
    // get directions input
    char directions[1000];
    if (fgets(directions, sizeof(directions), in) == NULL) {
        fclose(in);
        return 1;
    }
    char skip[10];
    fgets(skip, sizeof(skip), in); // skip line

    // populate nodes
    Node nodes[17576] = {0};
    int start = -1;
    int goal = -1;
    if (populate_nodes(in, nodes, &start, &goal) == 1) {
        return 1;
    }

    // simulate steps
    int len = strlen(directions);
    directions[len - 1] = '\0'; // remove newline
    len--;
    int pos = 0;
    (*steps) = 0;
    const int max_steps = 100000;

    // start and goal seems fixed
    start = 0;
    goal = 17575;
    Node *current = &nodes[start];
    while (*steps < max_steps) {
        if (current->code == goal) {
            break;
        }
        char dir = directions[pos];
        if (dir == 'L'){
            current = current->left;
        } else if (dir == 'R') {
            current = current->right;
        } else {
            return 1;
        }
        (*steps)++;
        pos = (pos + 1) % len;
    }
    return 0;
}

/**
 * Populates the nodes array from the input file.
 */
int populate_nodes(FILE* in, Node* nodes, int* start, int* goal)
{
    char buffer[20];
    while (fgets(buffer, sizeof(buffer), in) != NULL) {
        if (read_line(buffer, nodes, start, goal) == 1) {
            return 1;
        }
    }
    fclose(in);
    return 0;
}

/**
 * Reads a line from the input file and populates the nodes array.
 */
int read_line(const char* line, Node* nodes, int* start, int* goal)
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
    if (*start == -1) {
        *start = temp[0].code;
    }
    *goal = temp[0].code;
    nodes[temp[0].code].left = &nodes[temp[1].code];
    nodes[temp[0].code].right = &nodes[temp[2].code];
    return 0;
}


/**
 * Counts the number of steps required to complete the task defined in the input file.
 * @param filename The path to the input file.
 * @param steps Pointer to an integer where the result will be stored.
 */
int count_steps_v2(const char* filename, long long* steps){
    FILE* in = fopen(filename, "r");
    if (in == NULL){
        return 1;
    }
    // get directions input
    char directions[1000];
    if (fgets(directions, sizeof(directions), in) == NULL) {
        fclose(in);
        return 1;
    }
    char skip[10];
    fgets(skip, sizeof(skip), in); // skip line

    // populate nodes
    Node nodes[17576] = {0};
    int *start = NULL;
    int size;
    if (populate_nodes_v2(in, nodes, &start, &size) == 1) {
        free(start);
        return 1;
    }

    // simulate steps
    int len = strlen(directions);
    directions[len - 1] = '\0'; // remove newline
    len--;
    int pos = 0;
    (*steps) = 0;

    // find each cycle
    int cycle_from[size], cycle_len[size];
    bool clean_cycle = true;
    for (int i = 0; i < size; i++) {
        if (find_cycle(&nodes, start[i], &directions, len, &cycle_from[i], &cycle_len[i]) == 1) {
            free(start);
            return 1;
        }
        // printf("Start: %s, Cycle from step %d, length %d\n", nodes[start[i]].name, cycle_from[i], cycle_len[i]);
        if (cycle_from[i] != cycle_len[i]) {
            clean_cycle = false;
        }
    }

    // find step when all cycles align
    if (clean_cycle) {
        long long result = cycle_len[0];
        for (int i = 1; i < size; i++) {
            result = lcm(result, cycle_len[i]);
        }
        *steps = result;
    } else {
        *steps = find_sync_point(cycle_from, cycle_len, size);
    }
    free(start);
    return 0;
}


/**
 * Finds cycle information starting from a given node.
 * @param nodes Array of Node structures.
 * @param start The starting node code.
 * @param directions The string of directions to follow.
 * @param len The length of the directions string.
 * @param cycle_from Pointer to an integer where the starting step of the cycle will be stored.
 * @param cycle_len Pointer to an integer where the length of the cycle will be stored.
 * @return 0 on success, 1 on failure.
 */
int find_cycle(Node* nodes, const int start, const char* directions, const int len, int* cycle_from, int* cycle_len)
{
    *cycle_from = 0;
    *cycle_len = -1;
    int count = 0; // number of times reached goal
    int step = 0;
    int dir_pos = 0; // index of direction loop
    Node current = nodes[start];
    Record *cycle = NULL;
    int loop_limit = 100000000;
    int found = 0;
    while (count < loop_limit) {
        // cycle check
        if (is_end_with(&current, 'Z')) {
            // if previously reached goal, check records
            for (int i = 0; i < count; i++) {
                // cycle found
                if (cycle[i].dir_pos == dir_pos) {
                    *cycle_from = cycle[i].step;
                    *cycle_len = step - cycle[i].step;
                    found = 1;
                    break;
                }
            }
            if (found) { break;}
            Record *ptr = realloc(cycle, sizeof(Record) * (count + 1));
            if (ptr == NULL) {
                return 1;
            }
            cycle = ptr;
            cycle[count].dir_pos = dir_pos;
            cycle[count].step = step;
            count++;
        }
        // normal process directions
        char dir = directions[dir_pos];

        if (dir == 'L'){
            current = *(current.left);
        } else if (dir == 'R') {
            current = *(current.right);
        } else {
            free(cycle);
            return 1;
        }
        step++;
        dir_pos = (dir_pos + 1) % len;
    }
    free(cycle);
    return 0;
}


/**
 * Populates the nodes array from the input file.
 */
int populate_nodes_v2(FILE* in, Node* nodes, int** start, int* size)
{
    char buffer[20];
    *size = 0;
    while (fgets(buffer, sizeof(buffer), in) != NULL) {
        if (read_line_v2(buffer, nodes, start, size) == 1) {
            return 1;
        }
    }
    fclose(in);
    return 0;
}

/**
 * Reads a line from the input file and populates the nodes array.
 */
int read_line_v2(const char* line, Node* nodes, int** start, int* size)
{
    char names[3][4]; // this, left, right
    if (sscanf(line, "%s = (%s %s)", names[0], names[1], names[2]) != 3) {
        return 1;
    }
    int codes[3] = {0};
    for (int i = 0; i < 3; i++) {
        names[i][3] = '\0'; // ensure null-termination
        Node temp = create_node(names[i]);
        if (temp.is_valid == false) {
            return 1;
        }
        if (nodes[temp.code].is_valid == false) {
            nodes[temp.code] = temp;
        }
        codes[i] = temp.code;
    }
    
    if (is_end_with(&nodes[codes[0]], 'A')) {
        int *ptr = realloc(*start, ((*size) + 1) * sizeof(int));
        if (ptr == NULL) {
            return 1; // realloc failed
        }
        *start = ptr;
        (*start)[*size] = codes[0];
        (*size)++;
    }
    nodes[codes[0]].left = &nodes[codes[1]];
    nodes[codes[0]].right = &nodes[codes[2]];
    return 0;
}
