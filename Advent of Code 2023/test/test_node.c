#include "unity.h"
#include "node.h"


TEST_CASE(0, 0)
TEST_CASE(1, 28)
TEST_CASE(2, 16197)
TEST_CASE(3, -1)
TEST_CASE(4, -1)
TEST_CASE(5, -1)
TEST_CASE(6, -1)
void test_hash_code(const int index, const int expected){
    const char* test_string[] = {
        "AAA",
        "ABC",
        "XYZ",
        "",
        "B",
        "3&@",
        "ABCD"
    };
    int result = hash_code(test_string[index]);
    TEST_ASSERT_EQUAL(expected, result);
}

TEST_CASE(0, 11099, true)
TEST_CASE(1, 3655, true)
TEST_CASE(2, 14264, true)
void test_create_node(const int index, const int expected, bool is_valid){
    const char* test_string[] = {
        "QKX",
        "FKP",
        "VCQ"
    };
    Node result = create_node(test_string[index]);
    TEST_ASSERT_EQUAL(is_valid, result.is_valid);
    TEST_ASSERT_EQUAL(expected, result.code);
    TEST_ASSERT_TRUE(strcmp(result.name, test_string[index]) == 0);
}



// TEST_CASE(0, 11099, 12587, 16051, true)
// TEST_CASE(1, 3655, 6249, 6491, true)
// TEST_CASE(2, 14264, 15705, 12654, true)
// void test_create_node(const int index, const int expected, const int left, const int right, bool is_valid){
//     const char test_string[] = {
//         "QKX = (SQD, XTJ)",
//         "FKP = (JGJ, JPR)",
//         "VCQ = (XGB, SSS)"
//     };
//     Node result = create_node(test_string[index]);
//     TEST_ASSERT_EQUAL(is_valid, result.is_valid);
//     TEST_ASSERT_EQUAL(expected, result.code);
//     TEST_ASSERT_EQUAL(left, result.left->code);
//     TEST_ASSERT_EQUAL(right, result.right->code);
// }
