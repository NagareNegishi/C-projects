#include <stdio.h>
#include "day1.h"

int get_password(const char* filename, int* password){
    *password = 0;
    FILE* in = fopen(filename, "r");
    if (in == NULL) {
        return 1;
    }

    char line[100];
    int current = 50; // start point
    while (fgets(line, sizeof(line), in) != NULL) {
        if (process_line(line, &current) != 0) {
            fclose(in);
            *password = 0;
            return 1;
        }
        if (current == 0) {
            (*password)++;
        }
    }
    fclose(in);
    return 0;
}

int process_line(const char* line, int* current){
    // parse direction
    char c = line[0];
    Direction dir;
    switch (c) {
        case 'R':
            dir = RIGHT;
            break;
        case 'L':
            dir = LEFT;
            break;
        default:
            dir = NONE;
            break;
    }
    if (dir == NONE) {
        return 1;
    }

    // get number
    int num;
    if (sscanf(&line[1], "%d", &num) != 1) {
        return 1;
    }

    // rotate
    int temp;
    if (dir == RIGHT) {
        temp = (*current + num) % 100;
    } else {
        temp = (*current - num) % 100;
        if (temp < 0) {
            temp = temp + 100;
        }
    }
    // if (temp < 0 || 100 <= temp) {
    //     return 1;
    // }
    *current = temp;
    return 0;
}


// Version 2 functions
int get_password_v2(const char* filename, int* password){
    *password = 0;
    FILE* in = fopen(filename, "r");
    if (in == NULL) {
        return 1;
    }
    char line[100];
    int current = 50; // start point
    while (fgets(line, sizeof(line), in) != NULL) {
        if (process_line_v2(line, &current, password) != 0) {
            fclose(in);
            *password = 0;
            return 1;
        }
    }
    fclose(in);
    return 0;
}

int process_line_v2(const char* line, int* current, int* password){
    // parse direction
    char c = line[0];
    Direction dir;
    switch (c) {
        case 'R':
            dir = RIGHT;
            break;
        case 'L':
            dir = LEFT;
            break;
        default:
            dir = NONE;
            break;
    }
    if (dir == NONE) {
        *password = -1;
        return 1;
    }

    // get number
    int num;
    if (sscanf(&line[1], "%d", &num) != 1) {
        *password = -1;
        return 1;
    }

    // rotate
    int temp_pos;
    int passed_zero = 0;
    if (dir == RIGHT) {
        temp_pos = (*current + num) % 100;
        // passed_zero = (*current + num) / 100; // integer division only counts full passes
        int temp_num = num;
        while (temp_num > 0) {
            if ((*current + temp_num) > 100) {
                passed_zero++;
            }
            temp_num -= 100;
        }
    } else {
        temp_pos = (*current - num) % 100;
        if (temp_pos < 0) {
            temp_pos = temp_pos + 100;
        }
        
        // if (num < *current) { // can not reach 0
        //     passed_zero = 0;
        // } else {
        //     // passed_zero = (num - *current + 99) / 100; // +99 because we excluded current
        //     passed_zero = 1 + (num - *current - 1) / 100;
        // }


        // count passes over zero
        int temp_num = num;
        while (temp_num > 0) {
            if ((*current - temp_num) < 0) {
                passed_zero++;
            }
            temp_num -= 100;
        }
    }

    // range check (could be removed)
    if (temp_pos < 0 || 100 <= temp_pos) {
        perror("Invalid position.");
        return 1;
    }
    // update result
    *current = temp_pos;
    (*password) += passed_zero;
    return 0;
}
