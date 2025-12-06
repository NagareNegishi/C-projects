#include <stdio.h>
#include <stdlib.h>
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

int parse_problem(const char* input, Problem* problem){
    if (problem->size >= MAX_NUMBERS || input == NULL || problem == NULL) {
        return 1;
    }
    if (input[0] == '+' || input[0] == '*') {
        problem->operation = input[0];
    } else {
        long long value;
        if (sscanf(input, "%lld", &value) != 1) {
            return 1;
        }
        problem->numbers[problem->size] = value;
        problem->size += 1;
    }
    return 0;
}

int get_total(const char* filename, long long* total){
    *total = 0;
    FILE* in = fopen(filename, "r");
    if (in == NULL) {
        return 1;
    }
    char buffer[5000];
    Problem problems[2000] = {0};
    int problem_count = 0;
    while (fgets(buffer, sizeof(buffer), in) != NULL) {
        char* ptr = buffer;
        int index = 0;
        char temp[100];
        int count;
        while (sscanf(ptr, "%s%n", temp, &count) == 1) {
            if (parse_problem(temp, &problems[index]) != 0) {
                fclose(in);
                return 1;
            }
            index++;
            ptr += count;
        }
        if (index > problem_count) {
            problem_count = index;
        }
    }
    fclose(in);

    // Evaluate each problem and accumulate the total
    for (int i = 0; i < problem_count; i++) {
        long long result = evaluate_problem(&problems[i]);
        if (result == -1) {
            return 1;
        }
        *total += result;
    }
    return 0;
}