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
            if (range.is_valid == false) {
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
    if (sscanf(line, "%lld-%lld", &range.start, &range.end) == 2) {
        range.is_valid = true;
    }
    return range;
}

//part2
int count_total_range(const char* filename, long long* total){
    *total = 0;
    FILE* in = fopen(filename, "r");
    if (in == NULL) { return 1; }

    Range ranges[200];
    int range_count = 0;
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), in) != NULL) {
        if (strchr(buffer, '-')) {
            Range range = parse_range(buffer);
            if (range.is_valid == false) {
                *total = 0;
                fclose(in);
                return 1;
            }
            ranges[range_count] = range;
            range_count++;
        } else {
            break;
        }
    }
    fclose(in);

    // unfortunately, c does not have a List like Java, and implementing List is overkill for this task.
    bool overlapped = true;
    while (overlapped) {
        overlapped = false;
        for (int i = 0; i < range_count; i++) {
            for (int j = i + 1; j < range_count; j++) {
                if (is_overlapping(&ranges[i], &ranges[j])) {
                    ranges[i] = merge_ranges(&ranges[i], &ranges[j]);
                    // Remove ranges[j]
                    for (int k = j; k < range_count - 1; k++) {
                        ranges[k] = ranges[k + 1];
                    }
                    range_count--;
                    overlapped = true;
                    break;
                }
            }
        }
    }
    long long total_covered = 0;
    for (int i = 0; i < range_count; i++) {
        total_covered += (ranges[i].end - ranges[i].start + 1);
    }
    *total = total_covered;
    return 0;
}

bool is_overlapping(Range* r1, Range* r2){
    return !(r1->end < r2->start || r2->end < r1->start);
}

Range merge_ranges(Range* r1, Range* r2){
    Range merged;
    merged.start = (r1->start < r2->start) ? r1->start : r2->start;
    merged.end = (r1->end > r2->end) ? r1->end : r2->end;
    merged.is_valid = true;
    return merged;
}