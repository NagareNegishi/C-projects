#ifndef DAY_6_H
#define DAY_6_H

/**
 * Fixed-size array is not flexible.
 * However, I did enough dynamic memory allocation problems in the past.
 * This is attempt to see how fixed-size arrays work in C.
 */

#define MAX_NUMBERS 5
typedef struct {
    int numbers[MAX_NUMBERS];
    int size;
    char operation; // '+' or '*'
} Problem;

long long evaluate_problem(Problem* problem);

int parse_problem(const char* input, Problem* problem);

int get_total(const char* filename, long long* total);

int get_total_v2(const char* filename, long long* total);
#endif // DAY_6_H