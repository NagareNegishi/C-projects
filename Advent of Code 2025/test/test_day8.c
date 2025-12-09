#include "unity.h"
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include "day8.h"



void test_distance_between_points() {
    Point a = {162, 817, 812};
    Point b = {425, 690, 689};

    double expected = 316.90;
    double tolerance = 0.01;    // adjust based on precision needs
    double result = distance(&a, &b);
    TEST_ASSERT_DOUBLE_WITHIN(tolerance, expected, result);
}

void test_get_answer() {
    long long answer = 0;
    int result = get_answer("test/day8.txt", &answer);
    TEST_ASSERT_EQUAL_INT(0, result);
    TEST_ASSERT_EQUAL_INT64(40, answer);
    result = get_answer("fake.txt", &answer);
    TEST_ASSERT_EQUAL_INT(1, result);
    TEST_ASSERT_EQUAL_INT64(0, answer);
}

void test_generate_points() {
    int point_size = 0;
    Point points[MAX_N] = {0};
    int result = generate_points("test/day8.txt", points, &point_size);
    // int result = generate_points("src/input8.txt", points, &point_size);
    TEST_ASSERT_EQUAL(0, result);
    TEST_ASSERT_EQUAL(20, point_size);
    TEST_ASSERT_EQUAL(162, points[0].x);
    TEST_ASSERT_EQUAL(817, points[0].y);
    TEST_ASSERT_EQUAL(812, points[0].z);
    TEST_ASSERT_EQUAL(425, points[19].x);
    TEST_ASSERT_EQUAL(690, points[19].y);
    TEST_ASSERT_EQUAL(689, points[19].z);
}
