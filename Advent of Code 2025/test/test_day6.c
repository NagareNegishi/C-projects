#include "unity.h"
#include <stdlib.h>
#include <string.h>
#include "day6.h"


TEST_CASE(0, 5, '+', 15)
TEST_CASE(0, 5, '*', 120)
TEST_CASE(1, 3, '+', 60)
TEST_CASE(1, 3, '*', 6000)
void test_evaluate_problem(int index, const int size, const char operation ,long long expected) {
    const long long test_numbers[][5] = {
        {1, 2, 3, 4, 5},
        {10, 20, 30, 0, 0}
    };
    Problem problem = {0};
    memcpy(problem.numbers, test_numbers[index], size * sizeof(long long));
    problem.size = size;
    problem.operation = operation;
    long long result = evaluate_problem(&problem);
    TEST_ASSERT_EQUAL(expected, result);
}

void test_parse_problem(){
    Problem problem = {0};
    int result = parse_problem("123", &problem);
    TEST_ASSERT_EQUAL(0, result);
    TEST_ASSERT_EQUAL(1, problem.size);
    TEST_ASSERT_EQUAL('\0', problem.operation);
    TEST_ASSERT_EQUAL(123, problem.numbers[0]);
    result = parse_problem("45", &problem);
    TEST_ASSERT_EQUAL(0, result);
    TEST_ASSERT_EQUAL(2, problem.size);
    TEST_ASSERT_EQUAL(45, problem.numbers[1]);
    result = parse_problem("6", &problem);
    TEST_ASSERT_EQUAL(0, result);
    TEST_ASSERT_EQUAL(3, problem.size);
    TEST_ASSERT_EQUAL(6, problem.numbers[2]);
    result = parse_problem("*", &problem);
    TEST_ASSERT_EQUAL(0, result);
    TEST_ASSERT_EQUAL(3, problem.size);
    TEST_ASSERT_EQUAL('*', problem.operation);
}


void test_get_total(){
    long long total = 0;
    // int result = get_total("test/day6.txt", &total);
    int result = get_total("src/input6.txt", &total);
    TEST_ASSERT_EQUAL(0, result);
    TEST_ASSERT_EQUAL(4277556, total);
    result = get_total("fake.txt", &total);
    TEST_ASSERT_EQUAL(1, result);
    TEST_ASSERT_EQUAL(0, total);
}


// part2
TEST_CASE(0, 3, '*', 8544)
TEST_CASE(1, 3, '+', 625)
TEST_CASE(2, 3, '*', 3253600)
TEST_CASE(3, 3, '+', 1058)
void test_evaluate_problem_v2(int index, const int size, const char operation ,long long expected) {
    const long long test_numbers[][5] = {
        {64, 23 ,314},
        {51, 387, 215},
        {328, 64, 98},
        {123, 45, 6}
    };
    Problem problem = {0};
    memcpy(problem.numbers, test_numbers[index], size * sizeof(long long));
    problem.size = size;
    problem.operation = operation;
    long long result = evaluate_problem_v2(&problem);
    TEST_ASSERT_EQUAL(expected, result);
}

void test_get_total_v2(){
    long long total = 0;
    // int result = get_total_v2("test/day6.txt", &total);
    int result = get_total_v2("src/input6.txt", &total);
    TEST_ASSERT_EQUAL(0, result);
    TEST_ASSERT_EQUAL(4277556, total);
    result = get_total_v2("fake.txt", &total);
    TEST_ASSERT_EQUAL(1, result);
    TEST_ASSERT_EQUAL(0, total);
}