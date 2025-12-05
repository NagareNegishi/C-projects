#ifndef DAY_5_H
#define DAY_5_H
#include <stdbool.h>

typedef struct {
    long long start;
    long long end;
} Range;

bool in_range(long long value, Range* range);

int count_total(const char* filename, int* total);

Range parse_range(const char* line);

#endif // DAY_5_H