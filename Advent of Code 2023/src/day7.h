#ifndef DAY7_H
#define DAY7_H
#include "hand.h"
#include <stdio.h>

// determine the total winnings
int get_total(const char* filename, int* total);

Hand* populate_hands(FILE* in, int* size);

void rank_hands(Hand* hands, const int size);


#endif // DAY7_H