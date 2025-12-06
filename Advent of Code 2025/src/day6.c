#include <stdio.h>
// #include <stdlib.h>
#include "day6.h"

long long evaluate_problem(Problem* problem){
    long long result;
    if (problem->operation == '+') {
        result = 0;
    } else if (problem->operation == '*') {
        result = 1;
    } else {
        return -1; // Invalid operation
    }
    for (int i = 0; i < problem->size; i++) {
        if (problem->operation == '+') {
            result += problem->numbers[i];
        } else if (problem->operation == '*') {
            result *= problem->numbers[i];
        }
    }
    return result;
}

int parse_problem(const char* input, Problem* problem);

int get_total(const char* filename, long long* total);