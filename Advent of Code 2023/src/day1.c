#include <stdio.h>
#include <ctype.h>
#include "day1.h"

int get_calibration_value(char* line) {
    int first = -1;
    int last = -1;
    for (int i = 0; line[i] != '\0'; i++) {
        if (isdigit(line[i])) {
            last = line[i] - '0';
            if (first == -1) {
                first = line[i] - '0';
            }
        }
    }
    if (first == -1) {
        return 0;
    } else {
        return first*10 + last;
    }
}

int calculate_sum(char* filename, int* result)
{
    FILE *in;
    in = fopen(filename, "r");
    if (in == NULL) {
        perror("fail to open file\n");
        return -1;
    }
    int total = 0;
    char buffer[200];
    while (fgets(buffer, sizeof(buffer), in) != NULL) {
        total += get_calibration_value(buffer);
    }
    printf("total is : %d\n", total);

    if (fclose(in) == EOF) {
        perror("Error closing file\n");
        return -1;
    }
    *result = total;
    return 0;
}

// int main(){
//     int total;
//     if (calculate_sum("input.txt", &total) == -1) {
//         return 1;
//     }
//     return 0;
// }