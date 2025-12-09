#include "unity.h"
#include "day9.h"

void test_getMaxArea() {
    long long area = 0;
    // int result = getMaxArea("test/day9.txt", &area);
    int result = getMaxArea("src/input9.txt", &area);
    TEST_ASSERT_EQUAL(0, result);
    TEST_ASSERT_EQUAL(50, area);
    result = getMaxArea("fake.txt", &area);
    TEST_ASSERT_EQUAL(1, result);
    TEST_ASSERT_EQUAL(0, area);
}

void test_readPointsFromFile() {
    Point points[MAX_POINTS];
    int point_size = 0;
    int result = readPointsFromFile("test/day9.txt", points, &point_size);
    TEST_ASSERT_EQUAL(0, result);
    TEST_ASSERT_EQUAL(8, point_size);
    TEST_ASSERT_EQUAL(7, points[0].x);
    TEST_ASSERT_EQUAL(1, points[0].y);
    TEST_ASSERT_EQUAL(7, points[7].x);
    TEST_ASSERT_EQUAL(3, points[7].y);
}

void test_findBestCorners() {
    Point points[MAX_POINTS];
    int point_size = 0;
    int result = readPointsFromFile("test/day9.txt", points, &point_size);
    BestCorners corners = findBestCorners(points, point_size);
    TEST_ASSERT_EQUAL(2, corners.top_left.x);
    TEST_ASSERT_EQUAL(3, corners.top_left.y);
    TEST_ASSERT_EQUAL(11, corners.top_right.x);
    TEST_ASSERT_EQUAL(1, corners.top_right.y);
    TEST_ASSERT_EQUAL(2, corners.bottom_left.x);
    TEST_ASSERT_EQUAL(5, corners.bottom_left.y);
    TEST_ASSERT_EQUAL(11, corners.bottom_right.x);
    TEST_ASSERT_EQUAL(7, corners.bottom_right.y);
}