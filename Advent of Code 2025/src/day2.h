#ifndef DAY_2_H
#define DAY_2_H

int get_total_invalid_IDs(const char* filename, long long* total);

int process_ID_range(char* line, long long* total);

int find_repeated_sequence(const long long start, const long long end, long long* total);

long long get_candidate(long long num, int digit_len, long long* first_half);

long long get_next_candidate(long long first_half, int digit_len);

#endif // DAY_2_H