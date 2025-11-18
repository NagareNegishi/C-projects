#include "unity.h"
#include "day1.h"
#include <stdio.h>

void setUp(void) {
    // This is run before EACH TEST
}
void tearDown(void) {
    // This is run after EACH TEST
}

void test_1(){
    int result = get_calibration_value("abcd9efgh5adg2358gdsd6");
    TEST_ASSERT_EQUAL(96,result);
}

void test_2(){
    int result = get_calibration_value("abcd");
    TEST_ASSERT_EQUAL(0,result);
}

void test_3(){
    int result = get_calibration_value("5");
    TEST_ASSERT_EQUAL(55,result);
}

void test_4(){
    int result = get_calibration_value("5!!!!/\n9");
    TEST_ASSERT_EQUAL(59,result);
}

void test_5(){
    int result = get_calibration_value("5!!!!/\09");
    TEST_ASSERT_EQUAL(55,result);
}

void test_6(){
    int total = 0;
    int result = calculate_sum("input.txt", &total);
    TEST_ASSERT_EQUAL(-1,result);
    TEST_ASSERT_EQUAL(0,total);
}

void test_7(){
    int total = 0;
    int result = calculate_sum("Advent of Code/src/input.txt", &total);
    TEST_ASSERT_EQUAL(-1,result);
    TEST_ASSERT_EQUAL(0,total);
}

void test_8(){
    int total = 0;
    int result = calculate_sum("src/input.txt", &total);
    TEST_ASSERT_EQUAL(0,result);
    TEST_ASSERT_NOT_EQUAL(0,total);
    TEST_ASSERT_EQUAL(54573,total);
}