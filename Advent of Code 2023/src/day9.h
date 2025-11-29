#ifndef DAY9_H
#define DAY9_H

// read the file and calculate the total
int get_total(const char* filename, long long* total);

// read the line and extract the history value
int get_history(const char* line, long long * value);

// recursively calculate the history value
long long calculate_history(long long* list, int size);

// recursively calculate the history value
long long calculate_history_backwards(long long* list, int size);
#endif // DAY9_H