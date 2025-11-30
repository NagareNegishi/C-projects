#include "unity.h"
#include "point.h"
#include "day10.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void test_get_steps(){
    long steps = 0;
    // int result = get_steps("test/day10.txt", &steps);
    int result = get_steps("src/input10.txt", &steps);
    TEST_ASSERT_EQUAL(1, result);
    TEST_ASSERT_EQUAL(8, steps);
    result = get_steps("fake.txt", &steps);
    TEST_ASSERT_EQUAL(0, result);
    TEST_ASSERT_EQUAL(0, steps);
}


void test_read_map(){
    FILE* in = fopen("test/day10.txt", "r");
    int rows = 0;
    int cols = 0;
    Point start;
    char *result = read_map(in, &rows, &cols, &start);
    fclose(in);
    TEST_ASSERT_NOT_NULL(result);
    TEST_ASSERT_EQUAL(5, rows);
    TEST_ASSERT_EQUAL(5, cols);
    TEST_ASSERT_EQUAL(2, start.row);
    TEST_ASSERT_EQUAL(0, start.col);
    TEST_ASSERT_TRUE(start.is_vaild);
}

