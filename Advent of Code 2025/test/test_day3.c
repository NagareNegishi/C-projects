#include "unity.h"
#include "day3.h"
#include "helper.h"

void test_get_total(){
    int total;
    int result = get_total("test/day3.txt", &total);
    // int result = get_total("src/input3.txt", &total);
    TEST_ASSERT_EQUAL(0, result);
    TEST_ASSERT_EQUAL(357, total);
    result = get_total("fake.txt", &total);
    TEST_ASSERT_EQUAL(1, result);
    TEST_ASSERT_EQUAL(0, total);
}


TEST_CASE(0, 98, 0)
TEST_CASE(1, 89, 0)
TEST_CASE(2, 78, 0)
TEST_CASE(3, 92, 0)
TEST_CASE(4, 0, 1)
TEST_CASE(5, 0, 1)
TEST_CASE(6, 0, 1)
void test_get_joltage(const int index, int expected, int expected_result){
    const char* test_lines[] = {
        "987654321111111\n",
        "811111111111119\n",
        "234234234234278\n",
        "818181911112111\n",
        "ABCDEFGHIJKLMNO\n",
        "\n",
        "1\n"
    };
    int joltage;
    int result = get_joltage(test_lines[index], &joltage);
    TEST_ASSERT_EQUAL(expected_result, result);
    TEST_ASSERT_EQUAL(expected, joltage);
}

TEST_CASE(0, '9')
TEST_CASE(1, '8')
TEST_CASE(2, '7')
TEST_CASE(3, '9')
void test_get_first_part(const int index, char expected){
    const char* test_lines[] = {
        "987654321111111",
        "811111111111119",
        "234234234234278",
        "818181911112111"
    };
    char first;
    const int length = 15;
    int pos;
    int result = get_first_part(test_lines[index], length, &first, &pos);
    TEST_ASSERT_EQUAL(0, result);
    TEST_ASSERT_EQUAL(expected, first);
}


TEST_CASE(0, '8', 0)
TEST_CASE(1, '9', 0)
TEST_CASE(2, '8', 13)
TEST_CASE(3, '2', 6)
void test_get_second_part(const int index, char expected, int first_index){
    const char* test_lines[] = {
        "987654321111111",
        "811111111111119",
        "234234234234278",
        "818181911112111"
    };
    char second;
    const int length = 15;
    int result = get_second_part(test_lines[index], length, &second, first_index);
    TEST_ASSERT_EQUAL(0, result);
    TEST_ASSERT_EQUAL(expected, second);
}


void test_get_total_v2(){
    long long total;
    int result = get_total_v2("test/day3.txt", &total);
    // int result = get_total("src/input3.txt", &total);
    TEST_ASSERT_EQUAL(0, result);
    TEST_ASSERT_EQUAL(3121910778619, total);
    result = get_total("fake.txt", &total);
    TEST_ASSERT_EQUAL(1, result);
    TEST_ASSERT_EQUAL(0, total);
}

TEST_CASE(0, 987654321111, 0)
TEST_CASE(1, 811111111119, 0)
TEST_CASE(2, 434234234278, 0)
TEST_CASE(3, 888911112111, 0)
void test_get_high_joltage(const int index, long long expected, int expected_result){
    const char* test_lines[] = {
        "987654321111111\n",
        "811111111111119\n",
        "234234234234278\n",
        "818181911112111\n"
    };
    long long joltage;
    int result = get_high_joltage(test_lines[index], &joltage);
    TEST_ASSERT_EQUAL(expected_result, result);
    TEST_ASSERT_EQUAL(expected, joltage);
}