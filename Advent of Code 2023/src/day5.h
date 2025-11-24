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









//part 2 attempt 1
int get_closest_with_range(const char* filename, long long* closest, const char* goal);
int get_source_size_with_range(const char* sources, long long* size);
int get_source_with_range(const char* sources, long long size, long long* array);

#endif