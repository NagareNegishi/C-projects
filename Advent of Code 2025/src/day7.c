#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "helper.h"
#include "day7.h"

/**
 * Parse a line of beam input and return the split beams
 */
Beams split_beams(const char* line, Beams* previous_beams, int* total){
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
                (*total)++;
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
    *total = 0;
    FILE* in = fopen(filename, "r");
    if (in == NULL) {
        perror("Failed to open file");
        return 1;
    }

    char line[256];
    Beams beams = {0};
    int line_number = 1; // first line is not 0 its 1
    while (fgets(line, sizeof(line), in) != NULL) {
        // skip even lines
        if (line_number % 2 == 0) {
            line_number++;
            continue;
        }
        beams = split_beams(line, &beams, total);
        line_number++;
    }
    fclose(in);
    return 0;
}


// part 2
int get_total_v2(const char* filename, long long* total){
    *total = 0;
    FILE* in = fopen(filename, "r");
    if (in == NULL) {
        perror("Failed to open file");
        return 1;
    }

    char line[256];
    Beams beams = {0};
    int line_number = 1; // first line is not 0 its 1
    while (fgets(line, sizeof(line), in) != NULL) {
        // skip even lines
        if (line_number % 2 == 0) {
            line_number++;
            continue;
        }
        beams = split_beams(line, &beams, total);
        line_number++;
    }
    fclose(in);
    return 0;
}