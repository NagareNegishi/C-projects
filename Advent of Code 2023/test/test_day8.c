#include "unity.h"
#include "day8.h"
#include "node.h"


void test_count_steps()
{
    int steps;
    // int result = count_steps("test/day8.txt", &steps);
    // int result = count_steps("src/input8.txt", &steps);
    // int result = count_steps_v2("test/day8_2.txt", &steps);
    int result = count_steps_v2("src/input8.txt", &steps);
    TEST_ASSERT_EQUAL(0, result);
    TEST_ASSERT_EQUAL(6, steps);
    result = count_steps("fake.txt", &steps);
    TEST_ASSERT_EQUAL(1, result);
}


void test_populate_nodes()
{
    FILE* in = fopen("test/day8.txt", "r");
    if (in == NULL){
        return;
    }
    char directions[1000];
    fgets(directions, sizeof(directions), in); // skip line
    fgets(directions, sizeof(directions), in);

    Node nodes[17576] = {0};
    int start = -1;
    int goal = -1;
    int result = populate_nodes(in, nodes, &start, &goal);
    TEST_ASSERT_EQUAL(0, result);
    TEST_ASSERT_NOT_EQUAL(-1, start);
    TEST_ASSERT_NOT_EQUAL(-1, goal);
    TEST_ASSERT_TRUE(nodes[0].is_valid == true);
    TEST_ASSERT_TRUE(nodes[703].left->is_valid == true);
    TEST_ASSERT_TRUE(nodes[17575].right->is_valid == true);
    TEST_ASSERT_EQUAL(17575, nodes[17575].code);
    TEST_ASSERT_EQUAL(0, start);
    TEST_ASSERT_EQUAL(17575, goal);
}


TEST_CASE(0, 0, 0)
TEST_CASE(1, 0, 703)
TEST_CASE(2, 0, 1406)
TEST_CASE(3, 1 , 1406)
void test_read_line(const int index, const int expected, const int num)
{
    const char* test_strings[] = {
        "AAA = (BBB, CCC)",
        "BBB = (DDD, EEE)",
        "CCC = (ZZZ, GGG)",
        "CCC  (ZZZ, GGG)"
    };
    Node nodes[17576] = {0};
    int start = -1;
    int goal = -1;
    TEST_ASSERT_TRUE(nodes[num].is_valid == false);
    int result = read_line(test_strings[index], nodes, &start, &goal);
    TEST_ASSERT_EQUAL(expected, result);
    if (result == 0) {
        TEST_ASSERT_NOT_EQUAL(-1, start);
        TEST_ASSERT_NOT_EQUAL(-1, goal);
        TEST_ASSERT_TRUE(nodes[num].is_valid == true);
        TEST_ASSERT_TRUE(nodes[num].left->is_valid == true);
        TEST_ASSERT_TRUE(nodes[num].right->is_valid == true);
        TEST_ASSERT_EQUAL(num, nodes[num].code);
        TEST_ASSERT_EQUAL(start , nodes[num].code);
        TEST_ASSERT_EQUAL(goal , nodes[num].code);
    }
}
