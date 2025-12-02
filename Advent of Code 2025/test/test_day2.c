#include "unity.h"
#include "helper.h"
#include "day2.h"

void test_get_total_invalid_IDs(){
    long long total;
    // int result = get_total_invalid_IDs("test/day2.txt", &total);
    int result = get_total_invalid_IDs("src/input2.txt", &total);
    TEST_ASSERT_EQUAL(0, result);
    TEST_ASSERT_EQUAL(1227775554, total);
    result = get_total_invalid_IDs("fake.txt", &total);
    TEST_ASSERT_EQUAL(1, result);
}

// void test_process_ID_range(){
//     long long total = 0;
//     const char* line = "11-22,95-115,998-1012,1188511880-1188511890,222220-222224,1698522-1698528,446443-446449,38593856-38593862,565653-565659,824824821-824824827,2121212118-2121212124";
//     char *ptr = (char*)line;
//     int result = process_ID_range(ptr, &total);
//     TEST_ASSERT_EQUAL(0, result);
//     TEST_ASSERT_EQUAL(1227775554, total);
// }


void test_find_repeated_sequence(){
    long long total = 0;
    // 11-22: invalid IDs are 11, 22 → sum = 33
    int result = find_repeated_sequence(11, 22, &total);
    TEST_ASSERT_EQUAL(0, result);
    TEST_ASSERT_EQUAL(33, total);
    
    // 95-115: invalid ID is 99 → sum = 33 + 99 = 132
    result = find_repeated_sequence(95, 115, &total);
    TEST_ASSERT_EQUAL(0, result);
    TEST_ASSERT_EQUAL(132, total);
    
    // 998-1012: invalid ID is 1010 → sum = 132 + 1010 = 1142
    result = find_repeated_sequence(998, 1012, &total);
    TEST_ASSERT_EQUAL(0, result);
    TEST_ASSERT_EQUAL(1142, total);
    
    // 1188511880-1188511890: invalid ID is 1188511885 → sum = 1142 + 1188511885
    result = find_repeated_sequence(1188511880, 1188511890, &total);
    TEST_ASSERT_EQUAL(0, result);
    TEST_ASSERT_EQUAL(1142 + 1188511885, total);
    
    // 222220-222224: invalid ID is 222222 → sum = 1142 + 1188511885 + 222222
    result = find_repeated_sequence(222220, 222224, &total);
    TEST_ASSERT_EQUAL(0, result);
    TEST_ASSERT_EQUAL(1142 + 1188511885 + 222222, total);
    
    // 1698522-1698528: no invalid IDs → sum unchanged
    result = find_repeated_sequence(1698522, 1698528, &total);
    TEST_ASSERT_EQUAL(0, result);
    TEST_ASSERT_EQUAL(1142 + 1188511885 + 222222, total);
    
    // 446443-446449: invalid ID is 446446 → sum = 1142 + 1188511885 + 222222 + 446446
    result = find_repeated_sequence(446443, 446449, &total);
    TEST_ASSERT_EQUAL(0, result);
    TEST_ASSERT_EQUAL(1142 + 1188511885 + 222222 + 446446, total);
    
    // 38593856-38593862: invalid ID is 38593859 → final sum = 1227775554
    result = find_repeated_sequence(38593856, 38593862, &total);
    TEST_ASSERT_EQUAL(0, result);
    TEST_ASSERT_EQUAL(1227775554, total);
}

