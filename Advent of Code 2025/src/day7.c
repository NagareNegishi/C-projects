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
    Beams beams[150] = {0};
    int beams_count = 0;
    int line_number = 1;
    int node_count = 0;
    
    while (fgets(line, sizeof(line), in) != NULL) {
        // skip even lines
        if (line_number % 2 == 0) {
            line_number++;
            continue;
        }
        // For first line (beams_count = 0), pass empty beam to trigger 'S' search
        // For other lines, pass the previous beam
        if (beams_count == 0) {
            beams[0] = split_beams(line, &beams[0], &node_count);
        } else {
            beams[beams_count] = split_beams(line, &beams[beams_count - 1], &node_count);
        }
        beams_count++;
        line_number++;
    }
    fclose(in);

    // calculate number of paths to reach each
    long long paths[150][256] = {0};
    paths[0][beams[0].indexes[0]] = 1; // 1 path at the starting position

    for (int level = 0; level < beams_count - 1; level++) {
        for (int i = 0; i < beams[level].size; i++) {
            // check each path at this level
            int pos = beams[level].indexes[i];
            long long current_paths = paths[level][pos];
            
            // No paths to this position
            if (current_paths == 0) { continue; }
            
            // Check what happened at the next level
            int has_same = contains(beams[level + 1].indexes, beams[level + 1].size, pos);
            int has_left = contains(beams[level + 1].indexes, beams[level + 1].size, pos - 1);
            int has_right = contains(beams[level + 1].indexes, beams[level + 1].size, pos + 1);
            
            // if next level has any of these -> possible paths until current position is part of possible paths to next level
            if (has_same) { // Beam continued straight
                paths[level + 1][pos] += current_paths;
            } else if (has_left && has_right) { // Beam split
                paths[level + 1][pos - 1] += current_paths;
                paths[level + 1][pos + 1] += current_paths;
            }
        }
    }
    
    // Sum all paths at final level
    *total = 0;
    for (int i = 0; i < beams[beams_count - 1].size; i++) {
        int pos = beams[beams_count - 1].indexes[i];
        *total += paths[beams_count - 1][pos];
    }

    return 0;
}

