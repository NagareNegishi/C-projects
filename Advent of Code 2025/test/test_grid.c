#include "unity.h"
#include "grid.h"

Grid grid;

void setUp(void) {
    grid = create_grid("test/day4.txt");
}

void test_create_grid(){
    TEST_ASSERT_EQUAL(10, grid.rows);
    TEST_ASSERT_EQUAL(10, grid.cols);
    TEST_ASSERT_EQUAL(1, grid.is_valid);
    TEST_ASSERT_EQUAL('.', grid.cells[0][0]);
    TEST_ASSERT_EQUAL('@', grid.cells[2][2]);
}

void test_create_grid_invalid(){
    grid = create_grid("fake.txt");
    TEST_ASSERT_EQUAL(0, grid.is_valid);
}


TEST_CASE(0, 0, 0, 1, 0, 1, 1)
TEST_CASE(0, 9, 0, 1, 8, 9, 1)
TEST_CASE(9, 0, 8, 9, 0, 1, 1)
TEST_CASE(9, 9, 8, 9, 8, 9, 1)
TEST_CASE(0, 5, 0, 1, 4, 6, 1)
TEST_CASE(9, 6, 8, 9, 5, 7, 1)
TEST_CASE(6, 0, 5, 7, 0, 1, 1)
TEST_CASE(6, 9, 5, 7, 8, 9, 1)
TEST_CASE(6, 6, 5, 7, 5, 7, 1)
TEST_CASE(10, 9, 0, 0, 0, 0, 0)
TEST_CASE(5, -9, 0, 0, 0, 0, 0)
void test_create_position(int row, int col, int expected_top, int expected_bottom,
    int expected_left, int expected_right, int is_valid) {
    Position pos = create_position(row, col, &grid);
    TEST_ASSERT_EQUAL(row, pos.row);
    TEST_ASSERT_EQUAL(col, pos.col);
    TEST_ASSERT_EQUAL(expected_top, pos.top);
    TEST_ASSERT_EQUAL(expected_bottom, pos.bottom);
    TEST_ASSERT_EQUAL(expected_left, pos.left);
    TEST_ASSERT_EQUAL(expected_right, pos.right);
    TEST_ASSERT_EQUAL(is_valid, pos.is_valid);
}

// while I could check if the position itself has valid character, it's job of caller
// So I will only test valid positions here
TEST_CASE(0, 2, 3)
TEST_CASE(1, 0, 3)
TEST_CASE(1, 9, 4)
TEST_CASE(1, 1, 6)
TEST_CASE(9, 0, 1)
TEST_CASE(9, 5, 5)
TEST_CASE(7, 5, 6)
void test_count_target(int row, int col, int expected_count) {
    Position pos = create_position(row, col, &grid);
    int count = count_target(&grid, &pos, '@');
    TEST_ASSERT_EQUAL(expected_count, count);
}
