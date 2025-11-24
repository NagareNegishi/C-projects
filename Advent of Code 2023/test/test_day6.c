#include <unity.h>
#include "day6.h"

TEST_CASE(0, 3, 1)
TEST_CASE(1, 0, 1)
TEST_CASE(2, 0, 0)
TEST_CASE(3, 5, 1)
void test_get_race_count(int index, int expected_size, int expected_result) {
    int size;
    const char* test_strings[] = {
        "Time:      7  15   30",
        "Time:      ",
        "Time      ",
        "Time:      7  15 30  1 2 , 3 "
    };
    int result = get_race_count(test_strings[index], &size);
    TEST_ASSERT_EQUAL(expected_size, size);
    TEST_ASSERT_EQUAL(expected_result, result);
}


void test_read_Races() {
    FILE *in;
    in = fopen("test/day6.txt", "r");
    if (in == NULL) {
        perror("Fail to open file in test.\n");
        return;
    }
    char time_buffer[500];
    if (fgets(time_buffer, sizeof(time_buffer), in) == NULL) {
        perror("Fail to read input in test.\n");
        return;
    }
    char distance_buffer[500];
    if (fgets(distance_buffer, sizeof(time_buffer), in) == NULL) {
        perror("Fail to read input in test.\n");
        return;
    }
    Race *races = (Race*) calloc(3, sizeof(Race));
    if (races == NULL) {
        perror("Memory allocation failed in test.\n");
        return;
    }
    int result = read_Races(races, 3, time_buffer, distance_buffer);
    TEST_ASSERT_EQUAL(1, result);
    TEST_ASSERT_EQUAL(7,races->time);
    TEST_ASSERT_EQUAL(9,races->distance);
    TEST_ASSERT_EQUAL(0,races->ways);
    races++;
    TEST_ASSERT_EQUAL(15,races->time);
    TEST_ASSERT_EQUAL(40,races->distance);
    TEST_ASSERT_EQUAL(0,races->ways);
    races++;
    TEST_ASSERT_EQUAL(30,races->time);
    TEST_ASSERT_EQUAL(200,races->distance);
    TEST_ASSERT_EQUAL(0,races->ways);
}

void test_calculate_ways() {
    Race *races = (Race*) calloc(3, sizeof(Race));
    if (races == NULL) {
        perror("Memory allocation failed.\n");
        return;
    }
    int result = read_Races(races, 3,
        "Time:      7  15   30\n",
        "Distance:  9  40  200\n");
    TEST_ASSERT_EQUAL(1, result);
    for (Race *ptr = races; ptr < races + 3; ptr++) {
        calculate_ways(ptr);
    }
    TEST_ASSERT_EQUAL(4,races->ways);
    races++;
    TEST_ASSERT_EQUAL(8,races->ways);
    races++;
    TEST_ASSERT_EQUAL(9,races->ways);
    races++;
}

void test_analyse_races() {
    int result;
    int ret = analyse_races("test/day6.txt", &result);
    TEST_ASSERT_EQUAL(1, ret);
    TEST_ASSERT_EQUAL(288,result);
}