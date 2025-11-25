#include <unity.h>
#include <stdio.h>
#include <stdlib.h>
#include "day5_2.h"


// test get_source
void test_get_source() {
    FILE *in;
    in = fopen("test/day5.txt", "r");
    if (in == NULL) {
        perror("Fail to open file.\n");
        return;
    }
    int size;
    Range *list = get_source(in, &size);
    TEST_ASSERT_FALSE(list == NULL);
    TEST_ASSERT_EQUAL(79, list[0].start);
    TEST_ASSERT_EQUAL(14, list[0].range);
    TEST_ASSERT_EQUAL(55, list[1].start);
    TEST_ASSERT_EQUAL(13, list[1].range);
}
