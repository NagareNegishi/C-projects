#include "unity.h"
#include "day5.h"


TEST_CASe(10, true)
TEST_CASe(20, true)
TEST_CASe(15, true)
TEST_CASe(9 , false)
TEST_CASe(100, false)
void test_in_range(long long value, bool expected) {
    Range range = {10, 20};
    bool result = in_range(value, &range);
    TEST_ASSERT_EQUAL(expected, result);
}

void test_count_total() {
    int total = 0;
    int result = count_total("test/day5.txt", &total);
    TEST_ASSERT_EQUAL(0, result);
    TEST_ASSERT_EQUAL(3, total);
    result = count_total("fake.txt", &total);
    TEST_ASSERT_EQUAL(1, result);
    TEST_ASSERT_EQUAL(0, total);
}

void test_parse_range() {
    Range range = parse_range("5-15\n");
    TEST_ASSERT_EQUAL(5, range.start);
    TEST_ASSERT_EQUAL(15, range.end);
    range = parse_range("100-200\n");
    TEST_ASSERT_EQUAL(100, range.start);
    TEST_ASSERT_EQUAL(200, range.end);
}