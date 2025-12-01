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
    int count = 0;
    while (fgets(line, sizeof(line), in) != NULL) {
        count++;
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

