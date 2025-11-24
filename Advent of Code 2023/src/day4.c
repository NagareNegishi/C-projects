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
    fclose(in);
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

// count number of columns
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


// part 2
// read file -> each line
int count_cards(const char* filename, int* total)
{
    FILE *in;
    in = fopen(filename, "r");
    if (in == NULL) {
        perror("Fail to open file.");
        return 0;
    }
    
    // first count winning numbers for each card
    char buffer[200];
    int winning_count[500] = {0};
    int total_rounds  = 0;
    while (fgets(buffer, sizeof(buffer), in) != NULL) {
        winning_count[total_rounds] = get_winning_count(buffer);
        total_rounds++;
    }
    fclose(in);

    // Copy card based on winning count
    int card_count[500] = {0};
    // original card
    for (int i = 0; i < total_rounds; i++) {
        card_count[i] = 1;
    }
    for (int round = 0; round < total_rounds; round++) {
        for(int card = 0; card < card_count[round]; card++){
            for (int next = 1; next <= winning_count[round]; next++) {
                (card_count[round + next])++;
            }
        }
    }

    // Sum up all cards
    *total = 0;
    for (int i = 0; i < total_rounds; i++) {
        *total += card_count[i];
    }
    return 1;
}

// compare winning numbers / my numbers
int get_winning_count(char* card)
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
    int winning_count = 0;
    for (int i = 0; i < num_size; i++) {
        if (contains(win, win_size, num[i])) {
            winning_count++;
        }
    }
    return winning_count;
}



int main(){
    int total;
    count_cards("input4.txt", &total);
    printf("total is %d\n",total);
}


// int main(){
//     int total;
//     get_total("input4.txt", &total);
//     printf("total is %d\n",total);
// }