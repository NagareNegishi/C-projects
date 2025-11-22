#ifndef DAY4_H
#define DAY4_H

// read file -> each line
int get_total(const char* filename, int* total);
// compare winning numbers / my numbers
int check_card(char* card, int* total);
// count number of columns
void count_cols(const char* card, int* win_size, int* num_size);
// 1 = true, 0 = false
int contains(int* array, const int size, const int target);
#endif
