// #include "hand.h"
#include "hand_j.h"
#include "day7.h"
#include <stdio.h>
#include <stdlib.h>

// determine the total winnings
int get_total(const char* filename, long long* total)
{
    *total = 0;
    FILE *in = fopen(filename, "r");
    if (in == NULL) { return 1;}

    // convert file to Hand
    int size;
    Hand *hands = populate_hands(in, &size);
    fclose(in);
    if (hands == NULL) { return 1;}

    // rank them and get total
    rank_hands(hands, size);
    for (int i = 0; i < size; i++) {
        *total += get_winning_points(&hands[i]);
    }
    return 0;
}

Hand* populate_hands(FILE* in, int* size)
{
    *size = 0;
    char buffer[100];
    Hand *hands = NULL;
    while (fgets(buffer, sizeof(buffer), in) != NULL) {
        Hand hand = create_hand(buffer);
        if (!hand.is_valid) {
            free(hands);
            return NULL;
        }
        Hand *ptr = realloc(hands, sizeof(Hand) * ((*size) + 1));
        if (ptr == NULL) {
            free(hands);
            return NULL;
        }
        hands = ptr;
        hands[*size] = hand;
        (*size)++;
    }
    return hands;
}

void rank_hands(Hand* hands, const int size)
{
    qsort(hands, size, sizeof(Hand), compare_hand);
    for (int i = 0; i < size; i++) {
        hands[i].rank = i + 1;
    }
}

// int main() {
//     long long total;
//     get_total("input7.txt", &total);
//     printf("Total is: %lld", &total);
// }