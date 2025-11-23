#include <unity.h>
#include <stdio.h>
#include "day5.h"

// test get_source_size
TEST_CASE(0, 4, 1)
TEST_CASE(1, 0, 1)
TEST_CASE(2, 0, 0)
TEST_CASE(3, 8, 1)
TEST_CASE(4, 7, 1)
void test_get_source_size(int index, int expected_size, int expected_result) {
    const char* test_strings[] = {
        "seeds: 79 14 55 13",
        "seeds: ",
        "se",
        "seeds: 79 14 55 13 1 1 1    1",
        "seeds: 79 14 55 13 1 1 1 ,   1"
    };
    int size;
    int result = get_source_size(test_strings[index], &size);
    TEST_ASSERT_EQUAL(expected_size, size);
    TEST_ASSERT_EQUAL(expected_result, result);
}

// test get_source
TEST_CASE(0, 4, 1)
TEST_CASE(1, 0, 1)
TEST_CASE(2, 0, 0)
TEST_CASE(3, 8, 1)
TEST_CASE(4, 7, 1)
void test_get_source(int index, int size, int expected_result) {
    const char* test_strings[] = {
        "seeds: 79 14 55 13",
        "seeds: ",
        "se",
        "seeds: 79 14 55 13 1 1 1    1",
        "seeds: 79 14 55 13 1 1 1 ,   1"
    };

    long long sources[size];
    int result = get_source(test_strings[index], size, sources);
    TEST_ASSERT_EQUAL(expected_result, result);
    const int test_ints[] = {79, 14, 55, 13};
    if (index == 0) {
        for (int i = 0; i < size; i++) {
            TEST_ASSERT_EQUAL(test_ints[i], sources[i]);
        }
    }
}
