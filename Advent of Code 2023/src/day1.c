#include <stdio.h>
#include <ctype.h>
#include <string.h>
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
        total += get_calibration_value_part2(buffer);
    }
    printf("total is : %d\n", total);

    if (fclose(in) == EOF) {
        perror("Error closing file\n");
        return -1;
    }
    *result = total;
    return 0;
}


int get_calibration_value_part2(char* line) {
    int first = -1;
    int last = -1;
    char *firstPos;
    char *lastPos;
    for (char* ptr = line; *ptr != '\0'; ptr++) {
        if (isdigit(*ptr)) {
            last = *ptr - '0';
            lastPos = ptr;
            if (first == -1) {
                first = *ptr - '0';
                firstPos = ptr;
            }
        }
    }
    char nums[9][7] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    for (int i = 0; i < 9; i++) {
        char *pos = line;
        // need to find all occurrences for each number word
        while ((pos = strstr(pos, nums[i])) != NULL) {
            if (pos < firstPos || first == -1) {
                firstPos = pos;
                first = string_to_int(nums[i]); // can be i + 1
            }
            if (pos > lastPos || last == -1) {
                lastPos = pos;
                last = string_to_int(nums[i]); // can be i + 1
            }
            pos++; // move forward to find next occurrence
        }
    }
    if (first == -1) {
        return 0;
    } else {
        return first*10 + last;
    }
}

int string_to_int(const char* str) {
    if (strcmp(str, "one") == 0) {
        return 1;
    } else if (strcmp(str, "two") == 0) {
        return 2;
    } else if (strcmp(str, "three") == 0) {
        return 3;
    } else if (strcmp(str, "four") == 0) {
        return 4;
    } else if (strcmp(str, "five") == 0) {
        return 5;
    } else if (strcmp(str, "six") == 0) {
        return 6;
    } else if (strcmp(str, "seven") == 0) {
        return 7;
    } else if (strcmp(str, "eight") == 0) {
        return 8;
    } else if (strcmp(str, "nine") == 0) {
        return 9;
    } else {
        return -1;
    }
}


int main(){
    int total;
    if (calculate_sum("input.txt", &total) == -1) {
        return 1;
    }
    return 0;
}