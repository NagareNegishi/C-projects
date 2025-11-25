#ifndef DAY5_2_H
#define DAY5_2_H

typedef struct {
    long long start;
    long long range;
} Range;

// get the closest location
int get_closest(const char* filename, long long* closest, const char* goal);

// get source
Range* get_source(FILE* in, int* size);

// read destination category
int read_category(FILE* in, const char* goal);

// convert to next type
Range* convert(FILE* in, Range* before, int* size);

// cleanup resources
void cleanup(FILE* in, Range* list);

#endif