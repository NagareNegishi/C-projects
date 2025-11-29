#include "unity.h"
#include "point.h"
#include <stdbool.h>





// typedef enum {
//     UP = 0,
//     RIGHT,
//     DOWN,
//     LEFT,
//     NONE
// } Direction;
// start is special case
TEST_CASE(1, 1, 2, true, 1)// right of start
TEST_CASE(2, 2, 1, true, 2)// down of start
TEST_CASE(0, 1, 3, true, 3)
TEST_CASE(4, 5, 0, false, 4)// impossible case
void test_search_option(const int dir, const int row, const int col, bool is_valid, int out){
    const char *lines = "-L|F7"
                        "7S-7|"
                        "L|7||"
                        "-L-J|"
                        "L|-JF";
    Point result = search_option(dir, lines, row, col, 5, 5);
    TEST_ASSERT_EQUAL(out, result.out);
    TEST_ASSERT_EQUAL(row, result.row);
    TEST_ASSERT_EQUAL(col, result.col);
    TEST_ASSERT_EQUAL(is_valid, result.is_vaild);
}

void test_is_start(){
    Point current = { .row = 1, .col = 1 };
    Point start = { .row = 1, .col = 1, .tile = START};
    TEST_ASSERT_TRUE(is_start(&current, &start));
}


void test_can_connect(){
    Point current = { .row = 1, .col = 1, .tile = S_E, .out = RIGHT};
    TEST_ASSERT_TRUE(can_connect(&current, '7')); // right
    TEST_ASSERT_FALSE(can_connect(&current, '|')); // down
}
