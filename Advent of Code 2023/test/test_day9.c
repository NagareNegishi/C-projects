#include "unity.h"
#include "day9.h"
#include <stdlib.h>
#include <stdbool.h>


void test_get_total() {
    long long total = 0;
    // int result = get_total("test/day9.txt", &total);
    int result = get_total("src/input9.txt", &total);
    TEST_ASSERT_EQUAL(1, result);
    TEST_ASSERT_EQUAL_INT64(114, total);
    result = get_total("fake.txt", &total);
    TEST_ASSERT_EQUAL(0, result);
}

TEST_CASE(0, 1, 18)
TEST_CASE(1, 1, 28)
TEST_CASE(2, 1, 68)
TEST_CASE(3, 0, 0)
TEST_CASE(4, 0, 0)
TEST_CASE(5, 0, 0)
void test_get_history(const int index, const int expected, const long long expected_value) {
    const char* test_strings[] = {
        "0 3 6 9 12 15",
        "1 3 6 10 15 21",
        "10 13 16 21 30 45",
        "",
        "1",
        "A E I O U",
    };
    long long value;
    int result = get_history(test_strings[index], &value);
    TEST_ASSERT_EQUAL(expected, result);
    TEST_ASSERT_EQUAL_INT64(expected_value, value);
}


void test_calculate_history() {
    long long list1[] = {0, 3, 6, 9, 12, 15};
    TEST_ASSERT_EQUAL_INT64(18, calculate_history(list1, 6));
    long long list2[] = {1, 3, 6, 10, 15, 21};
    TEST_ASSERT_EQUAL_INT64(28, calculate_history(list2, 6));
    long long list3[] = {10, 13, 16, 21, 30, 45};
    TEST_ASSERT_EQUAL_INT64(68, calculate_history(list3, 6));
}