#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "day3.h"


// the sum of all of the part numbers
int get_sum(const char* filename, int* sum)
{
    // check dimension
    int max_row;
    int max_col;
    if (check_schematic_size(filename, &max_row, &max_col) == 1) {
        perror("check_schematic_size failed.");
        return 1;
    }
    // copy file to 2d Array
    char grid[max_row][max_col];
    if (copy_schematic(filename, (char*) grid, max_col) == 1) {
        perror("copy_schematic failed.");
        return 1;
    }
    // get sum
    *sum = 0;
    for (int r = 0; r < max_row; r++) {
        if (read_line(&grid[r][0], sum, max_row, max_col, r)) {
            perror("read_line failed.");
            return 1;
        }
    }
    return 0;
}

// scan file to get max rows and max columns while check format
int check_schematic_size(const char* filename, int* max_row, int* max_col)
{
    *max_row = 0;
    *max_col = 0;
    // open file
    FILE *in;
    in = fopen(filename, "r");
    if (in == NULL) {
        perror("Fail to open fill.");
        return 1;
    }
    // check dimension
    char buffer[200];
    while (fgets(buffer, sizeof(buffer), in)!= NULL) {
        int temp = strlen(buffer);
        // each line ends with '\n', which is not part of schematic
        if (temp > 0 && buffer[temp-1] == '\n') {
            temp--;
        }
        if (*max_col == 0) {
            *max_col = temp;
        } else {
            if (*max_col != temp) {
                perror("Schematic has inconsistent line length.");
                *max_row = 0;
                *max_col = 0;
                return 1;
            }
        }
        (*max_row)++;
    }
    // close file
    if (fclose(in) == EOF){
        perror("Fail to close fill.");
        return 1;
    }
    return 0;
}


// allocate 2D array based on max rows and max columns
// scan file again to populate 2D array
int copy_schematic(const char* filename, char* grid, const int max_col)
{
    // open file
    FILE *in;
    in = fopen(filename, "r");
    if (in == NULL) {
        perror("Fail to open fill.");
        return 1;
    }
    // line contains '\n' and need room for '\0' -> +2
    char buffer[max_col + 2];
    while (fgets(buffer, max_col + 2, in)!= NULL) {
        memcpy(grid, buffer, max_col); // remove '\n'
        grid += max_col;
    }
    // close file
    if (fclose(in) == EOF){
        perror("Fail to close fill.");
        return 1;
    }
    return 0;
}

// iterate through 2D array
// skip non-digit
// if digit, read number and length of number
int read_line(char* line, int* total, const int max_row, const int max_col, const int row)
{
    int num = 0;
    int len = 0;
    for (int i = 0; i < max_col; i++) {
        // digit -> update current number
        if (isdigit(line[i])) {
            int temp = line[i] - '0';
            num = num*10 + temp;
            len++;
            // case last col
            if (max_col - 1 == i) {
                int start = i - len + 1;
                if (check_surrounding(&line[start], num, len, max_row, max_col, row, start) == 1){
                    *total += num;
                }
                num = 0;
                len = 0;
            }
        }
        // end of digit
        else if (len != 0) {
            if (check_surrounding(&line[i - len], num, len, max_row, max_col, row, i - len) == 1){
                *total += num;
            }
            num = 0;
            len = 0;
        }
    }
    return 0;
}

// check surrounding cells
// if adjacent to a symbol, return 1, else -1
int check_surrounding(char* cursor, int num, int len, const int max_row, const int max_col,
    const int row, const int col)
{
    int top = (row > 0) ? row - 1: row;
    int bottom = (row == max_row - 1) ? row: row + 1;
    int left = (col == 0) ? col : col - 1;
    int right = (col + len >= max_col - 1) ? max_col - 1  : col + len;
    if (left < 0 || right >= max_col || top < 0 || bottom >= max_row) {
        perror("Target number is out of bounds.");
        return 0;
    }
    for (int r = top; r <= bottom; r++) {
        int r_offset = r - row;
        for (int c = left; c <= right; c++) {
            int c_offset = c - col;
            char ch = cursor[max_col * r_offset + c_offset];
            if (!isdigit(ch) && ch != '.') {
                return 1;
            }
        }
    }
    return 0;
}



// the sum of all of gear ratio
int get_sum_gear_ratio(const char* filename, long* sum)
{
    // check dimension
    int max_row;
    int max_col;
    if (check_schematic_size(filename, &max_row, &max_col) == 1) {
        perror("check_schematic_size failed.");
        return 1;
    }
    // copy file to 2d Array
    char grid[max_row][max_col];
    if (copy_schematic(filename, (char*) grid, max_col) == 1) {
        perror("copy_schematic failed.");
        return 1;
    }
    // get sum
    *sum = 0;
    for (int r = 0; r < max_row; r++) {
        if (spot_gear(&grid[r][0], sum, max_row, max_col, r)) {
            perror("read_line failed.");
            return 1;
        }
    }
    return 0;
}


// iterate through 2D array to spot '*'
int spot_gear(char* line, long* total, const int max_row, const int max_col, const int row)
{
    for (int i = 0; i < max_col; i++) {
        if (line[i] == '*') {
            (*total) += check_gear_ratio(line, max_row, max_col, row, i);
        }
    }
    return 0;
}

// check surrounding cells
// if adjacent to 2 numbers, return their product, else 0
long check_gear_ratio(char* cursor, const int max_row, const int max_col, const int row, const int col)
{
    int top = (row > 0) ? row - 1: row;
    int bottom = (row == max_row - 1) ? row: row + 1;
    int left = (col == 0) ? col : col - 1;
    int right = (col + 1 >= max_col - 1) ? col : col + 1;
    if (left < 0 || right >= max_col || top < 0 || bottom >= max_row) {
        perror("Target number is out of bounds.");
        return 0;
    }
    int first = -1;
    int second = -1;
    int count = 0;
    for (int r = top; r <= bottom; r++) {
        int r_offset = r - row;
        int last_num_pos = -1;
        for (int c = left; c <= right; c++) {
            char ch = cursor[max_col * r_offset + c];
            if (isdigit(ch)) {
                int start_pos;
                int num = extract_num(&cursor[max_col * r_offset], c, max_col, &start_pos);
                if (last_num_pos != start_pos) { // avoid double count
                    last_num_pos = start_pos;
                    count++;
                    if (count >= 3) {
                        return 0;
                    }
                    if (first == -1) {
                        first = num;
                    } else if (second == -1) {
                        second = num;
                    }
                }
            }
        }
    }
    if (count != 2) {
        return 0;
    }
    printf("Found gear ratio: %d * %d = %ld\n", first, second, (long)first * second);
    return (long)first * second;
}

int extract_num(char* line, const int col, const int max_col, int* start_pos)
{
    int start = col;
    while (start > 0 && isdigit(line[start - 1])) {
        start--;
    }
    int end = start;
    int num = 0;
    while (end < max_col && isdigit(line[end])) {
        num = num * 10 + (line[end] - '0');
        end++;
    }
    *start_pos = start;
    return num;
}


int main(){
    long sum;
    if (get_sum_gear_ratio("input3.txt", &sum) == 1) {
        perror("get_sum failed.");
        return 1;
    }
    printf("The sum is %ld\n", sum);
    return 0;
}


// int main(){
//     int sum;
//     if (get_sum("input3.txt", &sum) == 1) {
//         perror("get_sum failed.");
//         return 1;
//     }
//     printf("The sum is %d\n", sum);
//     return 0;
// }