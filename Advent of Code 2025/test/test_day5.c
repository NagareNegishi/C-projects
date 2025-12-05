#include "unity.h"
#include "day5.h"


TEST_CASE(10, true)
TEST_CASE(20, true)
TEST_CASE(15, true)
TEST_CASE(9 , false)
TEST_CASE(100, false)
void test_in_range(long long value, bool expected) {
    Range range = {10, 20};
    bool result = in_range(value, &range);
    TEST_ASSERT_EQUAL(expected, result);
}

void test_count_total() {
    int total = 0;
    int result = count_total("test/day5.txt", &total);
    // int result = count_total("src/input5.txt", &total);
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

// part 2
void test_count_total_range() {
    long long total = 0;
    int result = count_total_range("test/day5.txt", &total);
    // int result = count_total_range("src/input5.txt", &total);
    TEST_ASSERT_EQUAL(0, result);
    TEST_ASSERT_EQUAL(14, total);
    result = count_total_range("fake.txt", &total);
    TEST_ASSERT_EQUAL(1, result);
    TEST_ASSERT_EQUAL(0, total);
}

void test_is_overlapping() {
    Range r1 = {10, 20, true};
    Range r2 = {15, 25, true};
    Range r3 = {21, 30, true};
    TEST_ASSERT_TRUE(is_overlapping(&r1, &r2));
    TEST_ASSERT_FALSE(is_overlapping(&r1, &r3));
}

void test_merge_ranges() {
    Range r1 = {10, 20, true};
    Range r2 = {15, 25, true};
    Range merged = merge_ranges(&r1, &r2);
    TEST_ASSERT_EQUAL(10, merged.start);
    TEST_ASSERT_EQUAL(25, merged.end);
}
