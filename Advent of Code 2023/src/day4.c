#include <stdio.h>
#include <string.h>
#include "day4.h"

// read file -> each line
int get_total(const char* filename, int* total)
{
    *total = 0;
    FILE *in;
    in = fopen(filename, "r");
    if (in == NULL) {
        perror("Fail to open file.");
        return 1;
    }
    
    char buffer[200];
    while (fgets(buffer, sizeof(buffer), in) != NULL) {
        if (check_card((char*) buffer, total) == 0) {
            printf("check_card failed at %s", buffer);
            return 1;
        }
    }

}

// compare winning numbers / my numbers
int check_card(char* card, int* total)
{
    // skip over ':'
    char* ptr = strchr(card, ':');
    ptr++;
    // count columns
    int win_size = 0;
    int num_size = 0;
    count_cols(ptr, &win_size, &num_size);
    // read winning numbers
    int win[win_size];
    int count;
    for (int i = 0; i < win_size; i++) {
        sscanf(ptr, " %d%n", &win[i], &count);
        ptr += count;
    }
    // skip over '|'
    ptr = strchr(card, '|');
    ptr++;
    // read my numbers
    int num[num_size];
    for (int i = 0; i < num_size; i++) {
        sscanf(ptr, " %d%n", &num[i], &count);
        ptr += count;
    }
    // check if winning numbers are in my numbers
    int point = 0;
    for (int i = 0; i < num_size; i++) {
        if (contains(win, win_size, num[i])) {
            if (point == 0) {
                point = 1;
            } else {
                point *= 2;
            }
        }
    }
    *total += point;
    return 1;
}

void count_cols(const char* card, int* win_size, int* num_size)
{
    int num;
    int count;
    const char* ptr = card;
    while (sscanf(ptr, " %d%n", &num, &count) == 1) {
        (*win_size)++;
        ptr += count;
    }
    ptr = strchr(ptr, '|');
    ptr++;
    while (sscanf(ptr, " %d%n", &num, &count) == 1) {
        (*num_size)++;
        ptr += count;
    }
    // printf("win size: %d, num size : %d\n", *win_size, *num_size);
    // printf("ptr: %s\n", ptr);
    // printf("card: %s\n", card);
}

// 1 = true, 0 = false
int contains(int* array, const int size, const int target)
{
    for (int* ptr = array; ptr < array + size; ptr++) {
        // printf("ptr is: %d, target is %d\n", *ptr, target);
        if (*ptr == target) {
            return 1;
        }
    }
    return 0;
}


int main(){
    int total;
    get_total("input4.txt", &total);
    printf("total is %d\n",total);
}