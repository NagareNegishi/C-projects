#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "day9.h"

// read the file and calculate the total
int get_total(const char* filename, long long* total){
    *total = 0;
    FILE* in = fopen(filename, "r");
    if (in == NULL){
        return 0;
    }
    char buffer[2000];
    long long sum = 0;
    while (fgets(buffer, sizeof(buffer), in) != NULL) {
        long long value = 0;
        if (get_history(buffer, &value) == 0) {
            fclose(in);
            return 0;
        }
        sum += value;
    }
    fclose(in);
    *total = sum;
    return 1;
}

// read the line and extract the history value
int get_history(const char* line, long long * value){
    if (line == NULL || value == NULL) {
        return 0;
    }
    long long *list = NULL;
    int size = 0;
    long long num;
    const char *ptr = line;
    int offset;
    while (sscanf(ptr, "%lld%n", &num, &offset) == 1) {
        long long *temp = realloc(list, sizeof(long long) * (size + 1));
        if (temp == NULL) {
            *value = 0;
            free(list);
            return 0;
        }
        list = temp;
        list[size] = num;
        size++;
        ptr += offset;
    }

    if (size <= 1) { // nothing to compare
        *value = 0;
        free(list);
        return 0;
    }

    *value = calculate_history(list, size);
    // *value = calculate_history_backwards(list, size); // for backwards calculation
    free(list);
    return 1;
}

// recursively calculate the history value
long long calculate_history(long long* list, int size){
    long long next[size - 1];
    bool all_zero = true;
    for (int i = 1; i < size; i++) {
        long long first = list[i - 1];
        long long second = list[i];
        // long long diff = llabs(first - second);
        long long diff = second - first;
        next[i - 1] = diff;
        if (diff != 0) {
            all_zero = false;
        }
    }
    if (all_zero) {
        return list[size - 1];
    }
    return list[size - 1] + calculate_history(next, size - 1);
}


// recursively calculate the history value
long long calculate_history_backwards(long long* list, int size){
    long long next[size - 1];
    bool all_zero = true;
    for (int i = 1; i < size; i++) {
        long long first = list[i - 1];
        long long second = list[i];
        // long long diff = llabs(first - second);
        long long diff = second - first;
        next[i - 1] = diff;
        if (diff != 0) {
            all_zero = false;
        }
    }
    if (all_zero) {
        return list[0];
    }
    return list[0] - calculate_history_backwards(next, size - 1);
}