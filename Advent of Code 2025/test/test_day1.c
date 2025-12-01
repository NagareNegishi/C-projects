#include "unity.h"
#include "day1.h"

void test_get_password(){
    int password;
    int result = get_password("test/day1.txt", &password);
    // int result = get_password("src/input1.txt", &password);
    TEST_ASSERT_EQUAL(0, result);
    TEST_ASSERT_EQUAL(3, password);
    result = get_password("fake.txt", &password);
    TEST_ASSERT_EQUAL(1, result);
    TEST_ASSERT_EQUAL(0, password);
}

void test_process_line(){
    int current = 50;
    int result = process_line("L68", &current);
    TEST_ASSERT_EQUAL(0, result);
    TEST_ASSERT_EQUAL(82, current);
    result = process_line("L30", &current);
    TEST_ASSERT_EQUAL(0, result);
    TEST_ASSERT_EQUAL(52, current);
    result = process_line("R48", &current);
    TEST_ASSERT_EQUAL(0, result);
    TEST_ASSERT_EQUAL(0, current);
    result = process_line("W48", &current);
    TEST_ASSERT_EQUAL(1, result);
    TEST_ASSERT_EQUAL(0, current);
}
