#ifndef DAY5_H
#define DAY5_H

// get the closest location
int get_closest(const char* filename, long long* closest, const char* goal);

// get size of source
int get_source_size(const char* sources, int* size);

// get size of source
int get_source(const char* sources, int size, long long* array);

// read destination category
int read_category(FILE* in, const char* goal);

// convert to next type
int convert(FILE* in, long long* before, const int size);

#endif