#ifndef DAY_3_H
#define DAY_3_H

int get_total(const char* filename, int* total);

int get_joltage(const char* line, int* joltage);

int get_first_part(const char* line, const int length, char* first, int* index);

int get_second_part(const char* line, const int length, char* second, const int first_index);
#endif // DAY_3_H