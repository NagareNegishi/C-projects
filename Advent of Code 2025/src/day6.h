#ifndef DAY_6_H
#define DAY_6_H

typedef struct {
    long long *numbers;
    int size;
    char operation; // '+' or '*'
} Problem;

long long evaluate_problem(Problem* problem);

int parse_problem(const char* input, Problem* problem);

int get_total(const char* filename, long long* total);
#endif // DAY_6_H