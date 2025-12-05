#ifndef DAY_5_H
#define DAY_5_H
#include <stdbool.h>

typedef struct {
    long long start;
    long long end;
    int is_valid; // for part 2
} Range;

bool in_range(long long value, Range* range);

int count_total(const char* filename, int* total);

Range parse_range(const char* line);

//part2
int count_total_range(const char* filename, int* total);

bool is_overlapping(Range* r1, Range* r2);

Range merge_ranges(Range* r1, Range* r2);

#endif // DAY_5_H