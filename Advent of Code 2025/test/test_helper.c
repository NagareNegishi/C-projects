#include "unity.h"
#include "helper.h"
#include <math.h>

TEST_CASE(1, 2, -1)
TEST_CASE(2, 1, 1)
TEST_CASE(1, 1, 0)
void test_compare_int(const int arg1, const int arg2, const int expected){
    int result = compare_int(&arg1, &arg2);
    if (result > 0) {
        result = 1;
    } else if (result < 0){
        result = -1;
    }
    TEST_ASSERT_EQUAL(expected, result);
}


TEST_CASE(0, 3, 1, 1)
TEST_CASE(0, 3, 0, 0)
TEST_CASE(1, 3, 4, 1)
TEST_CASE(1, 3, 9, 0)
TEST_CASE(2, 3, 9, 1)
TEST_CASE(2, 2, 9, 0) // size less than actual array size
void test_contains(const int index, const int size, const int target, const int expected){
    const int* list[] = {
            (int[]){1, 2, 3},
            (int[]){4, 5, 6},
            (int[]){7, 8, 9}
        };
    int result = contains(list[index], size, target);
    TEST_ASSERT_EQUAL(expected, result);
}


TEST_CASE(0, 1)
TEST_CASE(5, 1)
TEST_CASE(10, 2)
TEST_CASE(123, 3)
TEST_CASE(-4567, 4)
void test_count_digits(long long num, int expected){
    int result = count_digits(num);
    TEST_ASSERT_EQUAL(expected, result);
}


TEST_CASE(0, 1)
TEST_CASE(5, 10)
TEST_CASE(10, 100)
TEST_CASE(123, 1000)
TEST_CASE(4567, 10000)
void test_next_power_of_10(long long n, long long expected){
    long long result = next_power_of_10(n);
    TEST_ASSERT_EQUAL(expected, result);
}