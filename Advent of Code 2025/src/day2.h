#ifndef DAY_2_H
#define DAY_2_H

int get_total_invalid_IDs(const char* filename, long long* total);

int process_ID_range(char* line, long long* total);

int find_repeated_sequence(const long long start, const long long end, long long* total);

#endif // DAY_2_H