#include "unity.h"
#include "day8.h"
#include "node.h"


// int count_steps(const char* filename, int* steps);

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
    Node start = {0};
    Node goal = {0};
    int result = populate_nodes(in, nodes, 17576, &start, &goal);
    TEST_ASSERT_EQUAL(0, result);
    TEST_ASSERT_TRUE(start.is_valid == true);
    TEST_ASSERT_TRUE(goal.is_valid == true);
    TEST_ASSERT_TRUE(nodes[0].is_valid == true);
    TEST_ASSERT_TRUE(nodes[703].left->is_valid == true);
    TEST_ASSERT_TRUE(nodes[17575].right->is_valid == true);
    TEST_ASSERT_EQUAL(17575, nodes[17575].code);
    TEST_ASSERT_EQUAL_STRING(start.name, "AAA");
    TEST_ASSERT_EQUAL_STRING(goal.name, "ZZZ");
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
    Node start = {0};
    Node goal = {0};
    TEST_ASSERT_TRUE(start.is_valid == false);
    TEST_ASSERT_TRUE(goal.is_valid == false);
    TEST_ASSERT_TRUE(nodes[num].is_valid == false);
    int result = read_line(test_strings[index], nodes, 17576, &start, &goal);
    TEST_ASSERT_EQUAL(expected, result);
    if (result == 0) {
        TEST_ASSERT_TRUE(start.is_valid == true);
        TEST_ASSERT_TRUE(goal.is_valid == true);
        TEST_ASSERT_TRUE(nodes[num].is_valid == true);
        TEST_ASSERT_TRUE(nodes[num].left->is_valid == true);
        TEST_ASSERT_TRUE(nodes[num].right->is_valid == true);
        TEST_ASSERT_EQUAL(num, nodes[num].code);
        TEST_ASSERT_EQUAL_STRING(start.name, nodes[num].name);
        TEST_ASSERT_EQUAL(goal.code, nodes[num].code);
    }
}


// Node* find_next(Node* current, const char direction);