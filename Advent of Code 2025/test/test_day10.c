#include "unity.h"
#include "day10.h"


void test_get_fewest_button_presses(){
    long long total;
    int result = get_fewest_button_presses("test/day10.txt", &total);
    // int result = get_fewest_button_presses("src/input10.txt", &total);
    TEST_ASSERT_EQUAL(0, result);
    TEST_ASSERT_EQUAL(7, total); // Replace with the expected total
    result = get_fewest_button_presses("fake.txt", &total);
    TEST_ASSERT_EQUAL(1, result);
    TEST_ASSERT_EQUAL(0, total);
}

TEST_CASE("[.##.] (3) (1,3) (2) (2,3) (0,2) (0,1) {3,5,4,7}\n", 2)
TEST_CASE("[...#.] (0,2,3,4) (2,3) (0,4) (0,1,2) (1,2,3,4) {7,5,12,7,2}\n", 3)
TEST_CASE("[.###.#] (0,1,2,3,4) (0,3,4) (0,1,2,4,5) (1,2) {10,11,11,5,10,5}\n", 7)
void test_check_machine(const char* line, const int expected){
    TEST_ASSERT_EQUAL(3, check_machine(line));
    TEST_ASSERT_EQUAL(-1, check_machine("invalid input\n"));
}

TEST_CASE("[.##.]", 0b0110)
TEST_CASE("[...#.]", 0b00010)
TEST_CASE("[.###.#]", 0b011101)
void test_convert_diagram(char* diagram, const uint16_t expected){
    TEST_ASSERT_EQUAL(expected, convert_diagram(diagram));
}

TEST_CASE("(3)", 0b1000)
TEST_CASE("(0,2,3,4)", 0b11101)
void test_convert_buttons(char* buttons, const uint16_t expected){
    TEST_ASSERT_EQUAL(expected, convert_buttons(buttons));
}
