#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "helper.h"
#include "day7.h"

/**
 * Parse a line of beam input and return the split beams
 */
Beams split_beams(const char* line, Beams* previous_beams){
    if (line == NULL) {
        perror("line is NULL!, nothing changes\n");
        return *previous_beams;
    }
    // then find start
    if (previous_beams->size == 0 ) {
        char *ret = strchr(line, 'S');
        if (ret == NULL) {
            perror("first line should have 'S', nothing changes\n");
            return *previous_beams;
        }
        int index = ret - line;
        previous_beams->indexes[0] = index;
        previous_beams->size = 1;
        return *previous_beams;
    }
    // then split beam
    else {
        Beams result = {0};
        // int new_size = 0;
        // int new_indexes[150] = {0};
        for (int i = 0; i < previous_beams->size; i++) {
            int index = previous_beams->indexes[i];
            char chr = line[index];
            if (chr == '.') { // just pass beans as it is
                if (!contains(result.indexes, result.size, index)) {
                    result.indexes[result.size] = index;
                    result.size++;
                }
            } else if (chr == '^') { // split beans
                int left = index - 1;
                int right = index + 1;
                if (!contains(result.indexes, result.size, left)) {
                    result.indexes[result.size] = left;
                    result.size++;
                }
                if (!contains(result.indexes, result.size, right)) {
                    result.indexes[result.size] = right;
                    result.size++;
                }
            }
        }
        return result;
    }
}

int get_total(const char* filename, int* total){
    return 0;
}