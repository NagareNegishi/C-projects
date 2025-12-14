#include "unity.h"
#include "day10.h"
#include "fff.h"

#define TEST_CASE(...)

void test_get_fewest_button_presses(){
    long long total;
    // int result = get_fewest_button_presses("test/day10.txt", &total);
    int result = get_fewest_button_presses("src/input10.txt", &total);
    TEST_ASSERT_EQUAL(0, result);
    TEST_ASSERT_EQUAL(7, total);
    result = get_fewest_button_presses("fake.txt", &total);
    TEST_ASSERT_EQUAL(1, result);
    TEST_ASSERT_EQUAL(0, total);
}


void test_check_machine(){
    TEST_ASSERT_EQUAL(2, check_machine("[.##.] (3) (1,3) (2) (2,3) (0,2) (0,1) {3,5,4,7}\n"));
    TEST_ASSERT_EQUAL(3, check_machine("[...#.] (0,2,3,4) (2,3) (0,4) (0,1,2) (1,2,3,4) {7,5,12,7,2}\n"));
    TEST_ASSERT_EQUAL(2, check_machine("[.###.#] (0,1,2,3,4) (0,3,4) (0,1,2,4,5) (1,2) {10,11,11,5,10,5}\n"));
    TEST_ASSERT_EQUAL(-1, check_machine("invalid input\n"));
}


void test_convert_diagram(){
    TEST_ASSERT_EQUAL(0b0110, convert_diagram("[.##.]"));
    TEST_ASSERT_EQUAL(0b00010, convert_diagram("[...#.]"));
    TEST_ASSERT_EQUAL(0b011101, convert_diagram("[.###.#]"));
}


void test_convert_buttons(){//
    TEST_ASSERT_EQUAL(0b0001, convert_buttons("(3)", 4));
    TEST_ASSERT_EQUAL(0b10111, convert_buttons("(0,2,3,4)", 5));
}

