#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "day2.h"

int get_sum_of_ID(const char* filename, int* result, const int max_r, const int max_g, const int max_b) {
    FILE *in;
    in = fopen(filename, "r");
    if (in == NULL) {
        perror("Fail to open file\n");
        return 1;
    }

    char buffer[200];
    int total = 0;
    while (fgets(buffer, sizeof(buffer),in) != NULL) {
        total += is_possible(buffer, max_r, max_g, max_b);
    }
    *result = total;
    if (fclose(in) == EOF){
        perror("Fail to close file\n");
        return 1;
    }
    return 0;
}

int is_possible(const char* line, const int max_r, const int max_g, const int max_b){
    // process game ID
    int round = 0;
    if (sscanf(line, "Game %d",&round) != 1) {
        perror("Wrong format of Game ID\n");
        return 0;
    }
    const char* current = strchr(line, ':');
    if (current == NULL) {
        perror("Wrong format of line, missing ':'\n");
        return 0;
    }
    current++;
    // process colors and numbers
    char color[6];
    int num = 0;
    int count;
    while (sscanf(current, " %d %[a-z]%n", &num, color, &count) == 2) {
        if ((strcmp(color, "red") == 0 && num > max_r) ||
            (strcmp(color, "green") == 0 && num > max_g) ||
            (strcmp(color, "blue") == 0 && num > max_b))
        {
            printf("Over the limit - Color: %s, Number: %d\n", color, num);
            return 0;
        }
        current += count;
        if (*current == ';' || *current == ',') {
            current++;
        }
    }
    return round;
}


int get_sum_of_power(const char* filename, int* result) {
    FILE *in;
    in = fopen(filename, "r");
    if (in == NULL) {
        perror("Fail to open file\n");
        return 1;
    }
    char buffer[200];
    int total = 0;
    while (fgets(buffer, sizeof(buffer),in) != NULL) {
        total += get_power(buffer);
    }
    *result = total;
    if (fclose(in) == EOF){
        perror("Fail to close file\n");
        return 1;
    }
    return 0;
}


int get_power(const char* line){
    const char* current = strchr(line, ':');
    if (current == NULL) {
        perror("Wrong format of line, missing ':'\n");
        return 0;
    }
    current++;

    // process colors and numbers
    char color[6];
    int num = 0;
    int max_r = 0;
    int max_g = 0;
    int max_b = 0;
    int count;
    while (sscanf(current, " %d %[a-z]%n", &num, color, &count) == 2) {
        if (strcmp(color, "red") == 0 && num > max_r) {
            max_r = num;
        } else if (strcmp(color, "green") == 0 && num > max_g) {
            max_g = num;
        } else if (strcmp(color, "blue") == 0 && num > max_b){
            max_b = num;
        }
        current += count;
        if (*current == ';' || *current == ',') {
            current++;
        }
    }
    int power = max_r * max_g * max_b;
    return power;
}


int main(){
    int result;
    if (get_sum_of_power("input2.txt", &result) == 1){
        perror("Fail to open/close file\n");
        return 1;
    }
    printf("total is: %d\n", result);
    return 0;
}



// int main(){
//     int result = 0, *ptr;
//     ptr = &result;
//     if (get_sum_of_ID("input2.txt", ptr, 12, 13, 14) == 1){
//         perror("Fail to open/close file\n");
//         return 1;
//     }
//     printf("total is: %d\n", *ptr);
//     return 0;
// }