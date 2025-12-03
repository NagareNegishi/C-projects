#ifndef DAY_3_H
#define DAY_3_H

int get_total(const char* filename, int* total);

int get_joltage(const char* line, int* joltage);

int get_first_part(const char* line, const int length, char* first, int* index);

int get_second_part(const char* line, const int length, char* second, const int first_index);

// part 2
int get_total_v2(const char* filename, long long* total);
int get_high_joltage(const char* line, long long* joltage);

// we know we need 12 digits, so pass current index and required digits
char get_best_digits(const char* line, int* current_index, const int requires, const int max_len);
#endif // DAY_3_H