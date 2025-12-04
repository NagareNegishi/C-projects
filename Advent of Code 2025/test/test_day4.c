#include "unity.h"
#include "day4.h"
#include "grid.h"


void test_count_total(){
    int total;
    // int result = count_total("test/day4.txt", &total);
    int result = count_total("src/input4.txt", &total);
    TEST_ASSERT_EQUAL(0, result);
    TEST_ASSERT_EQUAL(13, total);
    result = count_total("fake.txt", &total);
    TEST_ASSERT_EQUAL(1, result);
    TEST_ASSERT_EQUAL(0, total);
}

void test_count_total_v2(){
    int total;
    int result = count_total_v2("test/day4.txt", &total);
    // int result = count_total_v2("src/input4.txt", &total);
    TEST_ASSERT_EQUAL(0, result);
    TEST_ASSERT_EQUAL(43, total);
    result = count_total("fake.txt", &total);
    TEST_ASSERT_EQUAL(1, result);
    TEST_ASSERT_EQUAL(0, total);
}