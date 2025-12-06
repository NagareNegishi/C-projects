#include "unity.h"
#include "day6.h"


TEST_CASE(0, 5, '+', 15)
TEST_CASE(0, 5, '*', 120)
TEST_CASE(1, 3, '+', 60)
TEST_CASE(1, 3, '*', 6000)
void test_evaluate_problem_addition(int index, const int size, const char operation ,long long expected) {
    const long long* test_numbers[] = {
        (long long[]){1, 2, 3, 4, 5},
        (long long[]){10, 20, 30}
    };
    Problem problem = {0};
    problem.numbers = (long long*)test_numbers[index];
    problem.size = size;
    problem.operation = operation;
    long long result = evaluate_problem(&problem);
    TEST_ASSERT_EQUAL(expected, result);
}

void test_parse_problem(){
    Problem problem = {0};
    long long array[4] = {0};
    problem.numbers = array;
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
    int result = get_total("test/day6.txt", &total);
    TEST_ASSERT_EQUAL(0, result);
    TEST_ASSERT_EQUAL(4277556, total);
    result = get_total("fake.txt", &total);
    TEST_ASSERT_EQUAL(1, result);
    TEST_ASSERT_EQUAL(0, total);
}
