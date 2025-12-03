#include <stdio.h>
#include <string.h>
#include "day3.h"
#include "helper.h"

int get_total(const char* filename, int* total){
    *total = 0;
    FILE* in = fopen(filename, "r");
    if (in == NULL) {
        return 1;
    }

    char line[200];
    int sum = 0;
    while (fgets(line, sizeof(line), in) != NULL) {
        int joltage;
        if (get_joltage(line, &joltage) != 0) {
            fclose(in);
            return 1;
        }
        sum += joltage;
    }
    fclose(in);
    *total = sum;
    return 0;
}

int get_joltage(const char* line, int* joltage){
    *joltage = 0;
    int length = get_line_length(line) - 1; // exclude '\n'
    if (length < 2) {
        return 1;
    }
    char first;
    char second;
    int index;
    if (get_first_part(line, length, &first, &index) != 0) {
        return 1;
    }
    if (get_second_part(line, length, &second, index) != 0) {
        return 1;
    }
    char combine[3] = {first, second, '\0'};
    sscanf(combine, "%d", joltage);
    return 0;
}

int get_first_part(const char* line, const int length, char* first, int* index){
    *first = '0';
    char max = '0';
    *index = 0;
    // length - 1 is last num, but it can not be first
    for (int i = 0; i < (length - 1); i++) {
        // invalid
        if (! ((line[i] >= '0') && (line[i] <= '9')) ) {
            return 1;
        }
        if (line[i] > max) {
            max = line[i];
            *index = i;
            if (max == '9') { // maximum possible
                *first = max;
                return 0;
            }
        }
    }
    *first = max;
    return 0;
}

int get_second_part(const char* line, const int length, char* second, const int first_index){
    *second = '0';
    char max = '0';
    int i = (first_index == 0) ? 1 : first_index + 1;
    // can not be first element
    for (; i < length; i++) {
        // invalid
        if (! ((line[i] >= '0') && (line[i] <= '9')) ) {
            return 1;
        }
        if (line[i] > max) {
            max = line[i];
            if (max == '9') { // maximum possible
                *second = max;
                return 0;
            }
        }
    }
    *second = max;
    return 0;
}