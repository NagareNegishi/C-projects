#ifndef HELPER_H
#define HELPER_H
#include "helper.h"
/**
 * Compares two integers.
 * @param arg1 Pointer to the first integer.
 * @param arg2 Pointer to the second integer.
 * @return Negative value if *arg1 < *arg2, zero if *arg1 == *arg2, positive value if *arg1 > *arg2.
 */
int compare_int(const void *arg1, const void *arg2);


/**
 * Checks if a target integer is present in a list of integers.
 * @param list Pointer to the array of integers.
 * @param size Number of elements in the array.
 * @param target The integer to search for.
 * @return 1 if the target is found, 0 otherwise.
 */
int contains(const int* list, const int size, const int target);

/**
 * Counts the number of digits in an integer.
 * @param num The integer to count digits for.
 * @return The number of digits in the integer.
 */
int count_digits(long long num);

/**
 * Finds the next power of 10 greater than n.
 * if n = 222, return 1000
 * @param n The input number.
 * @return The next power of 10 greater than n.
 */
long long next_power_of_10(long long n);


/**
 * Gets the length of a line (string).
 * @param line The input string.
 * @return The length of the string.
 */
int get_line_length(const char* line);


#endif // HELPER_H