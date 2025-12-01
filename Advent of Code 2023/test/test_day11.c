#include "unity.h"
#include "day11.h"
#include "galaxy.h"
#include "helper/helper.h"
#include "helper/helper.c"


void test_get_sum(){
    long long sum = 0;
    // int result = get_sum("test/day11.txt", &sum);
    int result = get_sum("src/input11.txt", &sum);
    TEST_ASSERT_EQUAL_INT(0, result);
    TEST_ASSERT_EQUAL(374, sum);
}