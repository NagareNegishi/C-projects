#include <unity.h>
#include <stdio.h>
#include <stdlib.h>
#include "day5_2.h"
#include "mock_day5.h"
#include <string.h>

// fake test
// #ifndef FFF_GLOBALS_DEFINED
// #define FFF_GLOBALS_DEFINED
// DEFINE_FFF_GLOBALS;
// #endif

// FAKE_VALUE_FUNC(int, get_source_size_with_range, const char*, long long*);

int fake_get_source_size_with_range(const char* sources, long long* size) {
    char *ptr = strchr(sources, ':');
    *size = 0;
    if (ptr == NULL) {
        perror("':' not found.\n");
        return 0;
    }
    *size = 4;
    return 1;
}



FILE* in;

void setUp(void) {
    in = fopen("test/day5.txt", "r");
    if (in == NULL) {
        perror("Fail to open test file.\n");
        exit(1);
    }
}

void tearDown(void) {
    if (fclose(in) != 0) {
        perror("Fail to close test file.\n");
    }
}

// fake test
void test_custom_fake() {
    get_source_size_with_range_fake.custom_fake = fake_get_source_size_with_range;
    long long size;
    int result = get_source_size_with_range("seeds: 79 14 55 13", &size);
    TEST_ASSERT_EQUAL(4, size);
    TEST_ASSERT_EQUAL(1, result);
    result = get_source_size_with_range("seeds 79 14 55 13", &size);
    TEST_ASSERT_EQUAL(0, size);
    TEST_ASSERT_EQUAL(0, result);
}


// test get_source
void test_get_source() {
    int size;
    Range *list = get_source(in, &size);
    TEST_ASSERT_FALSE(list == NULL);
    TEST_ASSERT_EQUAL(79, list[0].start);
    TEST_ASSERT_EQUAL(14, list[0].range);
    TEST_ASSERT_EQUAL(55, list[1].start);
    TEST_ASSERT_EQUAL(13, list[1].range);
    free(list);
}

// test read_category
TEST_CASE(0, 2)
TEST_CASE(1, 2)
TEST_CASE(2, 1)
TEST_CASE(3, 1)
TEST_CASE(4, 2)
TEST_CASE(5, 1)
TEST_CASE(6, 2)
void test_read_category(int index, int expected_result) {
    const char* test_strings[] = {
        "seed",
        "soil",
        "location",
        "water",
        "-",
        "&",
        "\n"
    };
    char buffer[1000];
    fgets(buffer, sizeof(buffer), in);
    fgets(buffer, sizeof(buffer), in);
    int result = read_category(in, test_strings[index]);
    TEST_ASSERT_EQUAL(expected_result, result);
}

void test_read_category2() {
    fseek(in, 0, SEEK_END);
    int result = read_category(in, "seed");
    TEST_ASSERT_EQUAL(0, result);
}

void test_convert() {
    int size;
    Range *list = get_source(in, &size);
    TEST_ASSERT_FALSE(list == NULL);
    char buffer[1000];
    fgets(buffer, sizeof(buffer), in);
    fgets(buffer, sizeof(buffer), in);
    Range *converted = convert(in, list, &size);
    TEST_ASSERT_FALSE(converted == NULL);
    TEST_ASSERT_EQUAL(2, size);
    TEST_ASSERT_EQUAL(81, converted[0].start);
    TEST_ASSERT_EQUAL(14, converted[0].range);
    TEST_ASSERT_EQUAL(57, converted[1].start);
    TEST_ASSERT_EQUAL(13, converted[1].range);
    free(list);
    free(converted);
}
