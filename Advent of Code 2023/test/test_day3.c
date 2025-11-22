#include <unity.h>
#include "day3.h"
#include <stdio.h>
#include <stdlib.h>

// test check_schematic_size
void test_1(){
    int row;
    int col;
    int result = check_schematic_size("test/day3.txt", &row, &col);
    TEST_ASSERT_EQUAL(0, result);
    TEST_ASSERT_EQUAL(10, row);
    TEST_ASSERT_EQUAL(10, col);
}

void test_2(){
    int row;
    int col;
    int result = check_schematic_size("day3.txt", &row, &col);
    TEST_ASSERT_EQUAL(1, result);
    TEST_ASSERT_EQUAL(0, row);
    TEST_ASSERT_EQUAL(0, col);
}

// test copy_schematic
void test_3(){
    char grid[10][10];
    int result = copy_schematic("test/day3.txt", &grid[0][0], 10);
    TEST_ASSERT_EQUAL(0, result);
    char first[] = {'4','6','7','.','.','1','1','4','.','.'};
    for (int i = 0; i < sizeof(first); i++) {
        TEST_ASSERT_EQUAL(first[i], grid[0][i]);
    }
    for (int i = 0; i < 10; i++) {
        TEST_ASSERT_TRUE(grid[i][9] != '\n');
    }
}

void test_4(){
    char grid[10][10];
    int result = copy_schematic("day3.txt", &grid[0][0], 10);
    TEST_ASSERT_EQUAL(1, result);
    char first[] = {'4','6','7','.','.','1','1','4','.','.'};
    for (int i = 0; i < sizeof(first); i++) {
        TEST_ASSERT_NOT_EQUAL(first[i], grid[0][i]);
    }
}

// test read_line
void test_5(){
    printf("=======test_5 start=========\n");
    char grid[10][10];
    int result = copy_schematic("test/day3.txt", &grid[0][0], 10);
    int total = 0;
    read_line(&grid[0][0], &total, 10, 10, 0);
    TEST_ASSERT_EQUAL(467, total);
    read_line(&grid[1][0], &total, 10, 10, 1);
    TEST_ASSERT_EQUAL(467 + 0, total);
    read_line(&grid[2][0], &total, 10, 10, 2);
    TEST_ASSERT_EQUAL(467 + 35 + 633, total);
}

void test_6(){
    printf("=======test_6 start=========\n");
    char grid[10][10];
    int result = copy_schematic("test/day3-2.txt", &grid[0][0], 10);
    int total = 0;
    read_line(&grid[0][0], &total, 10, 10, 0);
    TEST_ASSERT_EQUAL(467, total);
    read_line(&grid[1][0], &total, 10, 10, 1);
    TEST_ASSERT_EQUAL(467 + 10, total);
    read_line(&grid[2][0], &total, 10, 10, 2);
    TEST_ASSERT_EQUAL(467 + 10 + 35 + 6, total);
    read_line(&grid[9][0], &total, 10, 10, 9);
    TEST_ASSERT_EQUAL(467 + 10 + 35 + 6 + 664, total);
}