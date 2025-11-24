#ifndef DAY3_H
#define DAY3_H

// the sum of all of the part numbers
int get_sum(const char* filename, int* sum);

// scan file to get max rows and max columns
int check_schematic_size(const char* filename, int* max_row, int* max_col);

// allocate 2D array based on max rows and max columns
// scan file again to populate 2D array
int copy_schematic(const char* filename, char* grid, const int max_col);

// iterate through 2D array
// skip non-digit
// if digit, read number and length of number
int read_line(char* line, int* total, const int max_row, const int max_col, const int row);

// check surrounding cells
int check_surrounding(char* cursor, int num, int len, const int max_row, const int max_col,
    const int row, const int col);

// part 2
int get_sum_gear_ratio(const char* filename, long* sum);
int spot_gear(char* line, long* total, const int max_row, const int max_col, const int row);
long check_gear_ratio(char* cursor, const int max_row, const int max_col, const int row, const int col);
int extract_num(char* line, const int col, const int max_col, int* start);
#endif // DAY3_H


