#include "unity.h"
#include "day7.h"

Beams split_beams(const char* line, Beams* previous_beams);

int get_total(const char* filename, int* total);

void test_split_beams(){
    Beams previous = {0};
    const char* line = ".......S.......\n";
    Beams result = split_beams(line, &previous);
    TEST_ASSERT_EQUAL(1, result.size);
    TEST_ASSERT_EQUAL(7, result.indexes[0]);
    result = split_beams(".......^.......\n", &result);
    TEST_ASSERT_EQUAL(2, result.size);
    TEST_ASSERT_EQUAL(6, result.indexes[0]);
    TEST_ASSERT_EQUAL(8, result.indexes[1]);
    result = split_beams("......^.^......\n", &result);
    TEST_ASSERT_EQUAL(3, result.size);
    TEST_ASSERT_EQUAL(5, result.indexes[0]);
    TEST_ASSERT_EQUAL(7, result.indexes[1]);
    TEST_ASSERT_EQUAL(9, result.indexes[2]);
    result = split_beams(".....^.^.^.....\n", &result);
    TEST_ASSERT_EQUAL(4, result.size);
    TEST_ASSERT_EQUAL(4, result.indexes[0]);
    TEST_ASSERT_EQUAL(6, result.indexes[1]);
    TEST_ASSERT_EQUAL(8, result.indexes[2]);
    TEST_ASSERT_EQUAL(10, result.indexes[3]);
    result = split_beams("....^.^...^....\n", &result);
    TEST_ASSERT_EQUAL(6, result.size);
    TEST_ASSERT_EQUAL(3, result.indexes[0]);
    TEST_ASSERT_EQUAL(5, result.indexes[1]);
    TEST_ASSERT_EQUAL(7, result.indexes[2]);
    TEST_ASSERT_EQUAL(8, result.indexes[3]);
    TEST_ASSERT_EQUAL(9, result.indexes[4]);
    TEST_ASSERT_EQUAL(11, result.indexes[5]);
    result = split_beams("...^.^...^.^...\n", &result);
    TEST_ASSERT_EQUAL(7, result.size);
    TEST_ASSERT_EQUAL(2, result.indexes[0]);
    TEST_ASSERT_EQUAL(4, result.indexes[1]);
    TEST_ASSERT_EQUAL(6, result.indexes[2]);
    TEST_ASSERT_EQUAL(7, result.indexes[3]);
    TEST_ASSERT_EQUAL(8, result.indexes[4]);
    TEST_ASSERT_EQUAL(10, result.indexes[5]);
    TEST_ASSERT_EQUAL(12, result.indexes[6]);
    result = split_beams("..^...^.....^..\n", &result);
    TEST_ASSERT_EQUAL(9, result.size);
    TEST_ASSERT_EQUAL(1, result.indexes[0]);
    TEST_ASSERT_EQUAL(3, result.indexes[1]);
    TEST_ASSERT_EQUAL(4, result.indexes[2]);
    TEST_ASSERT_EQUAL(5, result.indexes[3]);
    TEST_ASSERT_EQUAL(7, result.indexes[4]);
    TEST_ASSERT_EQUAL(8, result.indexes[5]);
    TEST_ASSERT_EQUAL(10, result.indexes[6]);
    TEST_ASSERT_EQUAL(11, result.indexes[7]);
    TEST_ASSERT_EQUAL(13, result.indexes[8]);
    result = split_beams(".^.^.^.^.^...^.\n", &result);
    TEST_ASSERT_EQUAL(9, result.size);
    TEST_ASSERT_EQUAL(0, result.indexes[0]);
    TEST_ASSERT_EQUAL(2, result.indexes[1]);
    TEST_ASSERT_EQUAL(4, result.indexes[2]);
    TEST_ASSERT_EQUAL(6, result.indexes[3]);
    TEST_ASSERT_EQUAL(8, result.indexes[4]);
    TEST_ASSERT_EQUAL(10, result.indexes[5]);
    TEST_ASSERT_EQUAL(11, result.indexes[6]);
    TEST_ASSERT_EQUAL(12, result.indexes[7]);
    TEST_ASSERT_EQUAL(14, result.indexes[8]);
}