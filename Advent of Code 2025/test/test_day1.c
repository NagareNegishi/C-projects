#include "unity.h"
#include "day1.h"

void test_get_password(){
    int password;
    int result = get_password("test/day1.txt", &password);
    // int result = get_password("src/input.txt", &password);
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


void test_get_password_v2(){
    int password;
    // int result = get_password_v2("test/day1.txt", &password);
    int result = get_password_v2("src/input.txt", &password);
    TEST_ASSERT_EQUAL(0, result);
    TEST_ASSERT_EQUAL(6, password);
    result = get_password_v2("fake.txt", &password);
    TEST_ASSERT_EQUAL(1, result);
    TEST_ASSERT_EQUAL(0, password);
}


void test_process_line_v2(){
    int current = 50;
    int count = 0;
    int result = process_line_v2("L68", &current, &count);
    TEST_ASSERT_EQUAL(0, result);
    TEST_ASSERT_EQUAL(82, current);
    TEST_ASSERT_EQUAL(1, count);
    result = process_line_v2("L30", &current, &count);
    TEST_ASSERT_EQUAL(0, result);
    TEST_ASSERT_EQUAL(52, current);
    TEST_ASSERT_EQUAL(1, count);
    result = process_line_v2("R48", &current, &count);
    TEST_ASSERT_EQUAL(0, result);
    TEST_ASSERT_EQUAL(0, current);
    TEST_ASSERT_EQUAL(2, count);
    result = process_line_v2("W48", &current, &count);
    TEST_ASSERT_EQUAL(1, result);
    TEST_ASSERT_EQUAL(0, current);
    TEST_ASSERT_EQUAL(-1, count);
}
