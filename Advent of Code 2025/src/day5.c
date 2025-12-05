#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "day5.h"

bool in_range(long long value, Range* range){
    return value >= range->start && value <= range->end;
}

int count_total(const char* filename, int* total){
    *total = 0;
    FILE* in = fopen(filename, "r");
    if (in == NULL) { return 1; }

    Range ranges[200];
    int range_count = 0;
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), in) != NULL) {
        if (strchr(buffer, '-')) {
            Range range = parse_range(buffer);
            if (range.start == -1) {
                *total = 0;
                fclose(in);
                return 1;
            }
            ranges[range_count] = range;
            range_count++;
        } else if (buffer[0] == '\n') {
            continue; // just skip
        } else { // its value line and all range is stored already
            long long value;
            if (sscanf(buffer, "%lld", &value) != 1) {
                *total = 0;
                fclose(in);
                return 1;
            }
            for (int i = 0; i < range_count; i++) {
                if (in_range(value, &ranges[i])) {
                    (*total)++;
                    break;
                }
            }
        }
    }
    fclose(in);
    return 0;
}

Range parse_range(const char* line){
    Range range = {0};
    if (sscanf(line, "%lld-%lld", &range.start, &range.end) != 2) {
        range.start = -1;
    }
    return range;
}