#include <unity.h>
#include "day2.h"
#include <stdio.h>
#include <stdlib.h>

void setUp(void) {
    // This is run before EACH TEST
}
void tearDown(void) {
    // This is run after EACH TEST
}

TEST_CASE(18, 18, 18, 38)
TEST_CASE(1, 1, 1, 0)
TEST_CASE(-100, -10, -50, 0)
void test_1(int max_r, int max_g, int max_b, int expected)
{
    int round = is_possible(
        "Game 38: 1 green, 4 blue, 17 red; 13 red, 9 blue, 12 green; 7 green, 11 blue\n",
        max_r, max_g, max_b
    );
    TEST_ASSERT_EQUAL(expected, round);
}

TEST_CASE(12, 13, 14, 8)
TEST_CASE(20, 13, 14, 11)
TEST_CASE(14, 13, 15, 12)
TEST_CASE(20, 13, 15, 15)
void test_2(int max_r, int max_g, int max_b, int expected)
{
    int total;
    int result = get_sum_of_ID("test/day2.txt", &total, max_r, max_g, max_b);
    TEST_ASSERT_EQUAL(expected, total);
    TEST_ASSERT_EQUAL(0, result);
}

TEST_CASE(12, 13, 14, 0)
void test_3(int max_r, int max_g, int max_b, int expected)
{
    int total;
    int result = get_sum_of_ID("day2.txt", &total, max_r, max_g, max_b);
    TEST_ASSERT_EQUAL(expected, total);
    TEST_ASSERT_EQUAL(1, result);
}
