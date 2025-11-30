#include <stdio.h>
#include "helper.h"

/**
 * Compares two integers.
 * @param arg1 Pointer to the first integer.
 * @param arg2 Pointer to the second integer.
 * @return Negative value if *arg1 < *arg2, zero if *arg1 == *arg2, positive value if *arg1 > *arg2.
 */
int compare_int(const void *arg1, const void *arg2){
    if (arg1 == NULL || arg2 == NULL) {
        perror("Null pointer passed to compare_int");
        return 0;
    }
    return (*(int*)arg1 - *(int*)arg2);
}


/**
 * Checks if a target integer is present in a list of integers.
 * @param list Pointer to the array of integers.
 * @param size Number of elements in the array.
 * @param target The integer to search for.
 * @return 1 if the target is found, 0 otherwise.
 */
int contains(const int* list, const int size, const int target){
    for (int i = 0; i < size; i++) {
        if (list[i] == target) {
            return 1;
        }
    }
    return 0;
}