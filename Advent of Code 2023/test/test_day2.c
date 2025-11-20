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
