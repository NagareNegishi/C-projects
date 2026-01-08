#include "unity.h"
#include "sys.h"

void setUp(void) {
    // This is run before EACH TEST
}
void tearDown(void) {
    // This is run after EACH TEST
}

void test_sys_io(void) {
    int result = sys_io();
    TEST_ASSERT_EQUAL(0, result);
}